import math
import numpy as np
from svg.path import parse_path
from xml.dom import minidom
import re
from Specification import points_to_steps
import sys

sys.path.append('../mi')
from MachineInstruction import MachineInstruction


class SVGInterpreter:
    """
    Interprets an SVG file and can generate files that can be run by the cnc.
    """

    def __init__(self, path, verbose=False):
        """
        Initializes the SVG interpreter with the given path. During initialization the interpreter gathers the objects
        from the SVG and sorts the objects to create an optimal tool path.
        :param path: The path of the '.svg' file.
        """
        self.verbose = verbose
        self.doc = minidom.parse(path)
        self.objects = []  # [['type', obj, 'sort-info'], ...]
        self.log("Gathering objects...", end='')
        for elem_type in ['line', 'polyline', 'polygon', 'path', 'rect', 'circle', 'ellipse']:
            for elem in self.doc.getElementsByTagName(elem_type):
                self.objects.append([elem_type, elem, SVGInterpreter.get_sort_info(elem_type, elem)])
        self.log("Completed.")
        if len(self.objects) == 0:
            self.log('[ERROR] No objects found.')
            return
        self.log("Optimizing object path...", end='')
        self.sort()
        self.log("Completed.")

    def log(self, s, end=None):
        """
        Logs a statement.
        """
        if self.verbose:
            if end:
                print(s, end=end)
            else:
                print(s)

    """
    Operations
    """

    @staticmethod
    def extract_transform(elem):
        """
        Extracts the transform from the element.
        :param elem: The element to get the transform from.
        :return: [[x, y], deg] the transform parameters.
        """
        transform_string = elem.getAttribute('transform')
        if transform_string:
            translate = re.search(r'(?<=translate\()[0-9\-. ]+', transform_string)
            if translate:
                translate = [float(x) for x in translate.group(0).split(' ')]
            else:
                translate = [0, 0]
            rotate = re.search(r'(?<=rotate\()[0-9\-. ]+', transform_string)
            if rotate:
                rotate = float(rotate.group(0))
            else:
                rotate = 0
            return [translate, rotate]
        return None

    @staticmethod
    def apply_transform(x, y, transform):
        """
        Applies the transform to the given xy coordinates.
        :param x: The x coordinate to transform.
        :param y: The y coordinate to transform.
        :param transform: [[x, y], deg] The transform to apply.
        :return: (x, y) The transformed coordinate.
        """
        if not transform:
            return x, y
        [[tx, ty], r] = transform
        xy = np.array([x, y, 1])
        if r:
            m2 = np.array([[math.cos(r * math.pi / 180), -math.sin(r * math.pi / 180), 0],
                           [math.sin(r * math.pi / 180), math.cos(r * math.pi / 180), 0],
                           [0, 0, 1]])
            xy = m2.dot(xy)
        if tx and ty:
            m1 = np.array([[1, 0, tx],
                           [0, 1, ty],
                           [0, 0, 1]])
            xy = m1.dot(xy)
        return xy[0], xy[1]

    @staticmethod
    def transform(elem, points):
        """
        Transforms a list of points with the given transform and then translates the points to steps.
        :param elem: The element to get the transform from.
        :param points: The list of points to transform.
        :return: The list of transformed and translated points.
        """
        transform = SVGInterpreter.extract_transform(elem)
        points = [SVGInterpreter.apply_transform(a, b, transform) for (a, b) in points]
        return [(points_to_steps(a), points_to_steps(b)) for (a, b) in points]

    """
    Helper methods.
    """

    def pop_object_minimizing_condition(self, condition):
        """
        Pops the objects that minimizes the condition given.
        :param condition: The condition.
        :return: The element the meets the condition.
        """
        sel = 0
        cur = math.inf
        for i in range(len(self.objects)):
            val = condition(self.objects[i][2])
            if val < cur:
                sel = i
                cur = val
        return self.objects.pop(sel)

    def sort(self):
        """
        Sorts the objects listed in self.objects to optimize the tool path.
        :return: None.
        """
        sorted_objects = [self.pop_object_minimizing_condition(lambda o: SVGInterpreter.distance((0, 0), o[0]))]
        while len(self.objects) > 0:
            sorted_objects.append(
                self.pop_object_minimizing_condition(lambda o: SVGInterpreter.distance(sorted_objects[-1][2][1], o[0]))
            )
        self.objects = sorted_objects

    @staticmethod
    def distance(a, b):
        """
        Computes the distance between 2 points.
        :param a: Point.
        :param b: Point.
        :return: The distance between them.
        """
        x0, y0 = a
        x1, y1 = b
        return math.sqrt((x1 - x0) ** 2 + (y1 - y0) ** 2)

    @staticmethod
    def compute_arc_point(origin, radius, deg):
        """
        Computes the point on an arc. Draws a line of length radius from the origin rotated by deg and returns the
        point at the end of the line.
        :param origin: The origin.
        :param radius: The radius.
        :param deg: The rotation deg amount.
        :return: The point.
        """
        origin = np.array(origin)
        point = np.array([0, -radius])
        theta = deg * (math.pi / 180.0)
        point = np.dot(point, np.array([
            [math.cos(theta), -math.sin(theta)],
            [math.sin(theta), math.cos(theta)]
        ]))
        point = point + origin
        return point[0], point[1]

    @staticmethod
    def compute_arc(origin, radius, start_deg, end_deg, samples):
        """
        Computes an arc between two degrees on a circle.
        :param origin: The origin of the circle.
        :param radius: The radius of the circle.
        :param start_deg: The degree to start at.
        :param end_deg: The degree to end at.
        :param samples: The number of samples to take to build the arc.
        :return: List of points that make up the arc.
        """
        points = []
        for x in range(int(samples)):
            p = x / samples
            deg = start_deg + (p * (end_deg - start_deg))
            point = SVGInterpreter.compute_arc_point(origin, radius, deg)
            if len(points) > 0 and points[-1] == point:
                continue
            points.append(point)
        return points

    @staticmethod
    def estimate_path_length(e):
        """
        Estimates the length of a path. This is used in place of more accurate calculations in order to save
        computational time. Computing the path length is done by taking the sum of the distance between a fixed
        number of samples points along the path.
        :param e: The path object.
        :return: The estimated length of the path.
        """
        length = 0
        estimate_frequency = 1000
        for i in range(estimate_frequency):
            p0 = e.point(1 / estimate_frequency * i)
            x0, y0 = p0.real, p0.imag
            p1 = e.point(1 / estimate_frequency * (i + 1))
            x1, y1 = p1.real, p1.imag
            length += math.sqrt((x1 - x0) ** 2 + (y1 - y0) ** 2)
        return length

    """
    Get appropriate properties from the element.
    """

    @staticmethod
    def get_line_info(elem):
        """
        Gets the line attributes from an element.
        :param elem: The element.
        :return: The line attributes.
        """
        x1 = float(elem.getAttribute('x1'))
        y1 = float(elem.getAttribute('y1'))
        x2 = float(elem.getAttribute('x2'))
        y2 = float(elem.getAttribute('y2'))
        return x1, y1, x2, y2

    @staticmethod
    def get_polyline_info(elem):
        """
        Gets the attributes from a polyline element.
        :param elem: The element.
        :return: List of points.
        """
        return [float(x) for x in elem.getAttribute('points').split(' ')]

    @staticmethod
    def get_rect_info(elem):
        """
        Gets the attributes from a rect element.
        :param elem: The element.
        :return: The rect attributes.
        """
        x = float(elem.getAttribute('x'))
        y = float(elem.getAttribute('y'))
        width = float(elem.getAttribute('width'))
        height = float(elem.getAttribute('height'))
        rx = elem.getAttribute('rx')
        if rx is not None and rx.isnumeric():
            rx = float(rx)
        else:
            rx = None
        return x, y, width, height, rx

    @staticmethod
    def get_path_info(elem):
        """
        Gets the attributes from a path element.
        :param elem: The element.
        :return: The path attributes.
        """
        return parse_path(elem.getAttribute('d'))

    @staticmethod
    def get_circle_info(elem):
        """
        Gets the attributes from a circle element.
        :param elem: The element.
        :return: The origin and radius.
        """
        origin = np.array([
            float(elem.getAttribute('cx')),
            float(elem.getAttribute('cy'))
        ])
        radius = float(elem.getAttribute('r'))
        return origin, radius

    @staticmethod
    def get_ellipse_info(elem):
        """
        Gets the attributes from an ellipse element.
        :param elem: The element.
        :return: The ellipse attributes.
        """
        cx = float(elem.getAttribute('cx'))
        cy = float(elem.getAttribute('cy'))
        rx = float(elem.getAttribute('rx'))
        ry = float(elem.getAttribute('ry'))
        return cx, cy, rx, ry

    """
    Parse methods.
    Each parse method operates on the raw point data from the element and returns a list of point tuples.
    """

    @staticmethod
    def parse_line(elem):
        """
        Parses a line.
        :param elem: The element.
        :return: List of point tuples.
        """
        x1, y1, x2, y2 = SVGInterpreter.get_line_info(elem)
        return [(x1, y1), (x2, y2)]

    @staticmethod
    def parse_polyline(elem):
        """
        Parses a polyline.
        :param elem: The element.
        :return: List of point tuples.
        """
        raw_points = SVGInterpreter.get_polyline_info(elem)
        return [(raw_points[i], raw_points[i + 1]) for i in range(0, len(raw_points) - 1, 2)]

    @staticmethod
    def parse_rect(elem):
        """
        Parses a rectangle.
        :param elem: The element.
        :return: List of point tuples.
        """
        x, y, width, height, rx = SVGInterpreter.get_rect_info(elem)
        points = []
        if rx is not None:
            t0x, t0y = x + rx, y
            t1x, t1y = x + width - rx, y
            r0x, r0y = x + width, y + rx
            r1x, r1y = x + width, y + height - rx
            b0x, b0y = x + width - rx, y + height
            b1x, b1y = x + rx, y + height
            l0x, l0y = x, y + height - rx
            l1x, l1y = x, y + rx
            points += [(t0x, t0y), (t1x, t1y)]
            samples = 2 * rx * math.pi
            points += SVGInterpreter.compute_arc((x + width - rx, y + rx), rx, -1, -90, samples)
            points += [(r0x, r0y), (r1x, r1y)]
            points += SVGInterpreter.compute_arc((x + width - rx, y + height - rx), rx, -91, -180, samples)
            points += [(b0x, b0y), (b1x, b1y)]
            points += SVGInterpreter.compute_arc((x + rx, y + height - rx), rx, -181, -270, samples)
            points += [(l0x, l0y), (l1x, l1y)]
            points += SVGInterpreter.compute_arc((x + rx, y + rx), rx, -271, -360, samples)
            points += [(t0x, t0y)]
        else:
            x0, y0 = x, y
            x1, y1 = x + width, y
            x2, y2 = x + width, y + height
            x3, y3 = x, y + height
            points += [(x0, y0), (x1, y1), (x2, y2), (x3, y3), (x0, y0)]
        return points

    @staticmethod
    def parse_path(elem):
        """
        Parses a path.
        :param elem: The element.
        :return: List of point tuples.
        """
        path = SVGInterpreter.get_path_info(elem)
        points = []
        for e in path:
            length = SVGInterpreter.estimate_path_length(e)
            if length == 0:
                continue
            samples = int(math.ceil(length))  # e.length() is significantly more intensive
            for i in range(samples + 1):
                p0 = e.point(1 / samples * i)
                points.append((p0.real, p0.imag))
        if len(points) > 0:
            return points
        return []

    @staticmethod
    def parse_circle(elem):
        """
        Parses a circle.
        :param elem: The element.
        :return: List of point tuples.
        """
        origin, radius = SVGInterpreter.get_circle_info(elem)
        circumference = 2 * math.pi * radius
        samples = math.ceil(circumference / 2)
        return SVGInterpreter.compute_arc(origin, radius, 0, 361, samples)

    @staticmethod
    def parse_ellipse(elem):
        """
        Parses an ellipse.
        :param elem: The element.
        :return: List of point tuples.
        """
        cx, cy, rx, ry = SVGInterpreter.get_ellipse_info(elem)
        points = []
        origin = (cx, cy)
        samples = 500
        for x in range(samples):
            deg = x / samples * 361.0
            s = (deg % 90) / 90.0
            if 90 < deg < 180 or 270 < deg < 360:
                s = 1 - s
            r = rx * s + ry * (1 - s)
            points.append(SVGInterpreter.compute_arc_point(origin, r, deg))
        return points

    """
    Sort info.
    """

    @staticmethod
    def get_sort_info(elem_type, elem):
        """
        Returns an array of 2 tuples giving sort information for the given element.
        :param elem_type: The type of the element (ex. circle, rect, line...).
        :param elem: The element.
        :return: [(float, float), (float, float)]
        """
        if elem_type == 'line':
            return SVGInterpreter.parse_line(elem)
        if elem_type == 'rect':
            x, y, _, _, _ = SVGInterpreter.get_rect_info(elem)
            return [(x, y), (x, y)]
        if elem_type == 'circle':
            origin, radius = SVGInterpreter.get_circle_info(elem)
            point = SVGInterpreter.compute_arc_point(origin, radius, 0)
            return [point, point]
        if elem_type == 'path':
            path = SVGInterpreter.get_path_info(elem)
            p0 = path[0].point(0)
            x0, y0 = p0.real, p0.imag
            p1 = path[-1].point(1)
            x1, y1 = p1.real, p1.imag
            return [(x0, y0), (x1, y1)]
        if elem_type == 'polyline' or elem_type == 'polygon':
            points = SVGInterpreter.get_polyline_info(elem)
            return [(points[0], points[1]), (points[-2], points[-1])]
        if elem_type == 'ellipse':
            cx, cy, _, _ = SVGInterpreter.get_ellipse_info(elem)
            return [(cx, cy), (cx, cy)]
        return [(0, 0), (0, 0)]

    """
    Iteration
    """

    def next(self):
        """
        Parses the next item.
        :return: The list of points from the item.
        """
        if len(self.objects) > 0:
            elem_type, elem, _ = self.objects.pop(0)
            points = []
            if elem_type == 'line':
                points = SVGInterpreter.parse_line(elem)
            if elem_type == 'polyline' or elem_type == 'polygon':
                points = SVGInterpreter.parse_polyline(elem)
            if elem_type == 'path':
                points = SVGInterpreter.parse_path(elem)
            if elem_type == 'rect':
                points = SVGInterpreter.parse_rect(elem)
            if elem_type == 'circle':
                points = SVGInterpreter.parse_circle(elem)
            if elem_type == 'ellipse':
                points = SVGInterpreter.parse_ellipse(elem)
            if len(points) == 0:
                return self.next()
            return SVGInterpreter.transform(elem, points)
        else:
            self.doc.unlink()
        return None

    """
    Creates a '.mi' file from the SVG.
    """

    def create_mi(self, path):
        """
        Creates an '.mi' file from the SVG.
        :param path: The output path.
        :return: None.
        """
        self.log("Parsing objects for '.mi' file...", end='')
        mi = MachineInstruction(path)

        def up():
            mi.append(MachineInstruction.coordinate('+0,+0,+40'))

        def down():
            mi.append(MachineInstruction.coordinate('+0,+0,0'))

        up()
        item = self.next()
        while item:
            mi.append(MachineInstruction.coordinate(f"{item[0][0]},{item[0][1]},+0"))
            down()
            for c in item[1:]:
                mi.append(MachineInstruction.coordinate(f"{c[0]},{c[1]},+0"))
            up()
            item = self.next()
        self.log("Completed.")
        mi.build()
        self.log("Generated '.mi' file.")

# SVG Interpreter

import math
import numpy as np
from svg.path import parse_path
from xml.dom import minidom
import re
from Specification import points_to_steps
import sys

sys.path.append('../ct')
from CTXML import CTXML


class SVGInterpreter:

    def __init__(self, filepath, skip=0, advanced_sort=True):
        self.doc = minidom.parse(filepath)
        self.sample_frequency = 1
        self.objects = []  # [['type', obj, 'sort-info'], ...]
        for obj in self.doc.getElementsByTagName('line'):
            self.objects.append(['line', obj, self.line_sort_info(obj)])
        for obj in self.doc.getElementsByTagName('polyline') + self.doc.getElementsByTagName('polygon'):
            self.objects.append(['polyline', obj, self.polyline_sort_info(obj)])
        for obj in self.doc.getElementsByTagName('path'):
            self.objects.append(['path', obj, self.path_sort_info(obj)])
        for obj in self.doc.getElementsByTagName('rect'):
            self.objects.append(['rect', obj, self.rect_sort_info(obj)])
        self.objects = sorted(self.objects, key=lambda x: x[2][0])
        if advanced_sort:
            sorted_objects = [self.objects.pop(0)]
            while len(self.objects) > 0:
                i_selection = 0
                i_length = math.inf
                for i in range(len(self.objects)):
                    dis = self.compute_object_distance(self.objects[i], sorted_objects[-1])
                    if dis < i_length:
                        i_length = dis
                        i_selection = i
                sorted_objects.append(self.objects.pop(i_selection))
            self.objects = sorted_objects
        for _ in range(skip):
            self.objects.pop(0)

    def compute_object_distance(self, a, b):
        x0, y0 = a[2][1]
        x1, y1 = b[2][0]
        return math.sqrt((x1 - x0) ** 2 + (y1 - y0) ** 2)

    # Extracts a transform from the filedata.
    def extract_transform(self, elem):
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

    # Applies a transform to the given x,y coordinates.
    def apply_transform(self, x, y, transform):
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

    # Parse rects from a doc, returns list of tuples containing [x, y, width, height]
    # for each rect adjusted from points to steps.
    def parse_rect(self, elem):
        x = float(elem.getAttribute('x'))
        y = float(elem.getAttribute('y'))
        width = float(elem.getAttribute('width'))
        height = float(elem.getAttribute('height'))
        x0, y0 = x, y
        x1, y1 = x + width, y
        x2, y2 = x + width, y + height
        x3, y3 = x, y + height
        transform = self.extract_transform(elem)
        x0, y0 = self.apply_transform(x0, y0, transform)
        x1, y1 = self.apply_transform(x1, y1, transform)
        x2, y2 = self.apply_transform(x2, y2, transform)
        x3, y3 = self.apply_transform(x3, y3, transform)
        x0, y0 = points_to_steps(x0), points_to_steps(y0)
        x1, y1 = points_to_steps(x1), points_to_steps(y1)
        x2, y2 = points_to_steps(x2), points_to_steps(y2)
        x3, y3 = points_to_steps(x3), points_to_steps(y3)
        return [(x0, y0), (x1, y1), (x2, y2), (x3, y3), (x0, y0)]

    # Parse paths from a doc, returns list of tuples containing [x, y]
    # for each point on the path adjusted from points to steps.
    def parse_path(self, elem):
        pd = elem.getAttribute('d')
        transform = self.extract_transform(elem)
        path = parse_path(pd)
        element_path = []
        for e in path:
            length = 0
            estimate_frequency = 1000
            for i in range(estimate_frequency):
                p0 = e.point(1 / estimate_frequency * i)
                x0, y0 = p0.real, p0.imag
                p1 = e.point(1 / estimate_frequency * (i + 1))
                x1, y1 = p1.real, p1.imag
                length += math.sqrt((x1 - x0) ** 2 + (y1 - y0) ** 2)
            if length == 0:
                continue
            samples = int(math.ceil(length * self.sample_frequency))  # e.length() is significantly more intensive
            sampled_path = []
            for i in range(samples + 1):
                p0 = e.point(1 / samples * i)
                x0, y0 = p0.real, p0.imag
                x0, y0 = self.apply_transform(x0, y0, transform)
                x0, y0 = points_to_steps(x0), points_to_steps(y0)
                sampled_path.append((x0, y0))
            element_path += sampled_path
        if len(element_path) > 0:
            return element_path
        return []

    def parse_polyline(self, elem):
        pnts = elem.getAttribute('points').split(' ')
        transform = self.extract_transform(elem)
        pnts = [float(x) for x in pnts]
        points = []
        for i in range(0, len(pnts) - 1, 2):
            x0, y0 = pnts[i], pnts[i + 1]
            x0, y0 = self.apply_transform(x0, y0, transform)
            points.append(
                (
                    points_to_steps(x0),
                    points_to_steps(y0)
                )
            )
        return points

    def parse_line(self, elem):
        l = [(points_to_steps(elem.getAttribute('x1')), points_to_steps(elem.getAttribute('y1'))),
             (points_to_steps(elem.getAttribute('x2')), points_to_steps(elem.getAttribute('y2')))]
        return l

    def rect_sort_info(self, elem):
        points = self.parse_rect(elem)
        return [points[0], points[-1]]

    def path_sort_info(self, elem):
        pd = elem.getAttribute('d')
        transform = self.extract_transform(elem)
        path = parse_path(pd)
        p0 = path[0].point(0)
        x0, y0 = p0.real, p0.imag
        p1 = path[-1].point(1)
        x1, y1 = p1.real, p1.imag
        x0, y0 = self.apply_transform(x0, y0, transform)
        x1, y1 = self.apply_transform(x1, y1, transform)
        return [(points_to_steps(x0), points_to_steps(y0)), (points_to_steps(x1), points_to_steps(y1))]

    def line_sort_info(self, elem):
        return self.parse_line(elem)

    def polyline_sort_info(self, elem):
        pnts = elem.getAttribute('points').split(' ')
        transform = self.extract_transform(elem)
        pnts = [float(x) for x in pnts]
        points = []
        for i in [0, len(points) - 2]:
            x0, y0 = pnts[i], pnts[i + 1]
            x0, y0 = self.apply_transform(x0, y0, transform)
            points.append(
                (
                    points_to_steps(x0),
                    points_to_steps(y0)
                )
            )
        return points

    # Gets the next item
    def next(self):
        if len(self.objects) > 0:
            obj = self.objects.pop(0)
            if obj[0] == 'line':
                return self.parse_line(obj[1])
            if obj[0] == 'polyline':
                return self.parse_polyline(obj[1])
            if obj[0] == 'path':
                return self.parse_path(obj[1])
            if obj[0] == 'rect':
                return self.parse_rect(obj[1])
        else:
            self.doc.unlink()
        return None

    def create_ctxml(self, path):
        ctxml = CTXML(path)
        ctxml.define_routine('pen-up', ['+0,+0,40'])
        ctxml.define_routine('pen-down', ['+0,+0,0'])
        ctxml.add_routine('pen-up')
        item = self.next()
        while item:
            ctxml.add_coordinate(f"{item[0][0]},{item[0][1]},+0")
            ctxml.add_routine('pen-down')
            for c in item[1:]:
                ctxml.add_coordinate(f"{c[0]},{c[1]},+0")
            ctxml.add_routine('pen-up')
            item = self.next()
        ctxml.close()

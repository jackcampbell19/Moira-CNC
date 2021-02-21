import xml.etree.ElementTree as et


class CoordinateTrace:

    def __init__(self, path, name):
        self.file = open(path, 'w')
        self.writeline(f"n {name}")
        self.writeline('{')

    def add_coordinate(self, xyz):
        x, y, z = xyz
        self.writeline(f"{x},{y},{z}")

    def writeline(self, line):
        self.file.writelines([line, '\n'])

    def close(self):
        self.writeline('}')
        self.file.close()

    @staticmethod
    def convert_xml(xml_path, ct_path):
        xml = et.parse(xml_path)
        root = xml.getroot()
        metadata = root.find('metadata')
        if metadata is None:
            raise Exception(f"[ERROR] <metadata> tag missing.")
        prnt = root.find('print')
        if prnt is None:
            raise Exception(f"[ERROR] <print> tag missing.")
        sequence = prnt.find('sequence')
        if sequence is None:
            raise Exception(f"[ERROR] <sequence> tag missing.")
        routines = prnt.find('routines')
        ct = CoordinateTrace(ct_path, metadata.find('name').text)

        routine_map = {}
        if routines is not None:
            for definition in routines:
                id_tag = definition.find('id')
                if id_tag is None or len(id_tag.text) == 0:
                    raise Exception(f"[ERROR] Routine id missing.")
                routine_map[id_tag.text] = definition.find('actions')
                if routine_map[id_tag.text] is None:
                    raise Exception(f"[ERROR] Routine '{id_tag.text}' is missing actions.")

        def helper_int_eval(i, prev):
            if i.isnumeric():
                return int(i)
            elif i.startswith('+'):
                return prev + int(i[1:])
            elif i.startswith('-'):
                return prev - int(i[1:])
            raise Exception(f"[ERROR] Value could not be converted properly: {i}")

        def helper_process_pos_tag(tag_text, prev_vals):
            split_text = tag_text.split(',')
            if len(split_text) != 3:
                raise Exception(f"[ERROR] <pos> tag format not accepted: <pos>{tag_text}</pos>")
            x, y, z = split_text
            x = helper_int_eval(x, prev_vals[0])
            y = helper_int_eval(y, prev_vals[1])
            z = helper_int_eval(z, prev_vals[2])
            return [x, y, z]

        prev_xyz = [0, 0, 0]
        for child in sequence:
            if child.tag == 'pos':
                xyz = helper_process_pos_tag(child.text, prev_xyz)
                ct.add_coordinate(xyz)
                prev_xyz = xyz
            elif child.tag == 'routine':
                if child.text not in routine_map:
                    raise Exception(f"[ERROR] Routine '{child.text}' does not exist.")
                for pos in routine_map[child.text]:
                    xyz = helper_process_pos_tag(pos.text, prev_xyz)
                    ct.add_coordinate(xyz)
                    prev_xyz = xyz
            else:
                raise Exception(f"[ERROR] Unexpected child tag of <sequence>: <{child.tag}>")

        ct.close()


CoordinateTrace.convert_xml('example.xml', 'test.ct')

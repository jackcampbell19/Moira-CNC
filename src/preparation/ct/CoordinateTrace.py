import xml.etree.ElementTree as et

from CTXML import ELEMENT_METADATA, ELEMENT_PRINT, ELEMENT_ROUTINES, ELEMENT_SEQUENCE, ELEMENT_DEFINE, ELEMENT_ID, \
    ELEMENT_ACTIONS, ELEMENT_COORDINATE, ELEMENT_ROUTINE


class CoordinateTrace:

    def __init__(self, path):
        self.file = open(path, 'w')

    def add_coordinate(self, xyz):
        x, y, z = xyz
        self.writeline(f"c {x},{y},{z}")

    def writeline(self, line):
        self.file.writelines([line, '\n'])

    def close(self):
        self.file.close()

    @staticmethod
    def from_ctxml(xml_path, ct_path):
        xml = et.parse(xml_path)
        root = xml.getroot()
        metadata = root.find(ELEMENT_METADATA)
        if metadata is None:
            raise Exception(f"[ERROR] <{ELEMENT_METADATA}> tag missing.")
        prnt = root.find(ELEMENT_PRINT)
        if prnt is None:
            raise Exception(f"[ERROR] <{ELEMENT_PRINT}> tag missing.")
        sequence = prnt.find(ELEMENT_SEQUENCE)
        if sequence is None:
            raise Exception(f"[ERROR] <{ELEMENT_SEQUENCE}> tag missing.")
        routines = prnt.find(ELEMENT_ROUTINES)
        ct = CoordinateTrace(ct_path)

        routine_map = {}
        if routines is not None:
            for definition in routines:
                id_tag = definition.find(ELEMENT_ID)
                if id_tag is None or len(id_tag.text) == 0:
                    raise Exception(f"[ERROR] Routine {ELEMENT_ID} missing.")
                routine_map[id_tag.text] = definition.find(ELEMENT_ACTIONS)
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
                raise Exception(f"[ERROR] <{ELEMENT_COORDINATE}> tag format not accepted:"
                                f" <{ELEMENT_COORDINATE}>{tag_text}</{ELEMENT_COORDINATE}>")
            x, y, z = split_text
            x = helper_int_eval(x, prev_vals[0])
            y = helper_int_eval(y, prev_vals[1])
            z = helper_int_eval(z, prev_vals[2])
            return [x, y, z]

        prev_xyz = [0, 0, 0]
        for child in sequence:
            if child.tag == ELEMENT_COORDINATE:
                xyz = helper_process_pos_tag(child.text, prev_xyz)
                ct.add_coordinate(xyz)
                prev_xyz = xyz
            elif child.tag == ELEMENT_ROUTINE:
                if child.text not in routine_map:
                    raise Exception(f"[ERROR] Routine '{child.text}' does not exist.")
                for pos in routine_map[child.text]:
                    xyz = helper_process_pos_tag(pos.text, prev_xyz)
                    ct.add_coordinate(xyz)
                    prev_xyz = xyz
            else:
                raise Exception(f"[ERROR] Unexpected child tag of <{ELEMENT_SEQUENCE}>: <{child.tag}>")

        ct.close()

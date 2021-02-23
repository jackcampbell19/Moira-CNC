from xml.dom import minidom


ELEMENT_DATA = 'data'
ELEMENT_METADATA = 'metadata'
ELEMENT_PRINT = 'print'
ELEMENT_ROUTINES = 'routines'
ELEMENT_SEQUENCE = 'sequence'
ELEMENT_DEFINE = 'define'
ELEMENT_ID = 'id'
ELEMENT_ACTIONS = 'actions'
ELEMENT_COORDINATE = 'coordinate'
ELEMENT_ROUTINE = 'routine'


class CTXML:

    def __init__(self, path):
        self.file = open(path, 'w')
        self.root = minidom.Document()
        self.xml = self.root.createElement(ELEMENT_DATA)
        self.root.appendChild(self.xml)
        self.metadata = self.root.createElement(ELEMENT_METADATA)
        self.xml.appendChild(self.metadata)
        self.print = self.root.createElement(ELEMENT_PRINT)
        self.xml.appendChild(self.print)
        self.routines = self.root.createElement(ELEMENT_ROUTINES)
        self.print.appendChild(self.routines)
        self.sequence = self.root.createElement(ELEMENT_SEQUENCE)
        self.print.appendChild(self.sequence)

    def define_routine(self, id_str, actions_list):
        define = self.root.createElement(ELEMENT_DEFINE)
        self.routines.appendChild(define)
        id = self.root.createElement(ELEMENT_ID)
        id.appendChild(self.root.createTextNode(id_str))
        define.appendChild(id)
        actions = self.root.createElement(ELEMENT_ACTIONS)
        define.appendChild(actions)
        for act in actions_list:
            action = self.root.createElement(ELEMENT_COORDINATE)
            action.appendChild(self.root.createTextNode(act))
            actions.appendChild(action)

    def add_coordinate(self, coordinate_str):
        pos = self.root.createElement(ELEMENT_COORDINATE)
        pos.appendChild(self.root.createTextNode(coordinate_str))
        self.sequence.appendChild(pos)

    def add_routine(self, routine_id):
        routine = self.root.createElement(ELEMENT_ROUTINE)
        routine.appendChild(self.root.createTextNode(routine_id))
        self.sequence.appendChild(routine)

    def close(self):
        self.file.write(self.root.toprettyxml(indent="\t"))
        self.file.close()

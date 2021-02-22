from xml.dom import minidom


class CTXML:

    def __init__(self, path):
        self.file = open(path, 'w')
        self.root = minidom.Document()
        self.xml = self.root.createElement('data')
        self.root.appendChild(self.xml)
        self.metadata = self.root.createElement('metadata')
        self.xml.appendChild(self.metadata)
        self.print = self.root.createElement('print')
        self.xml.appendChild(self.print)
        self.routines = self.root.createElement('routines')
        self.print.appendChild(self.routines)
        self.sequence = self.root.createElement('sequence')
        self.print.appendChild(self.sequence)

    def define_routine(self, id_str, actions_list):
        define = self.root.createElement('define')
        self.routines.appendChild(define)
        id = self.root.createElement('id')
        id.appendChild(self.root.createTextNode(id_str))
        define.appendChild(id)
        actions = self.root.createElement('actions')
        define.appendChild(actions)
        for act in actions_list:
            action = self.root.createElement('pos')
            action.appendChild(self.root.createTextNode(act))
            actions.appendChild(action)

    def add_pos(self, pos_str):
        pos = self.root.createElement('pos')
        pos.appendChild(self.root.createTextNode(pos_str))
        self.sequence.appendChild(pos)

    def add_routine(self, routine_id):
        routine = self.root.createElement('routine')
        routine.appendChild(self.root.createTextNode(routine_id))
        self.sequence.appendChild(routine)

    def close(self):
        self.file.write(self.root.toprettyxml(indent="\t"))
        self.file.close()

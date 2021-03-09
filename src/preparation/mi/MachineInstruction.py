class MachineInstruction:

    def __init__(self, path):
        self.path = path
        self.instructions = []

    def append(self, instruction):
        self.instructions.append(instruction)

    @staticmethod
    def coordinate(xyz):
        return f"c {xyz}\n"

    @staticmethod
    def special(id, payload):
        return f"s {id} {payload}\n"

    @staticmethod
    def wait(milliseconds):
        return f"w {milliseconds}\n"

    def build(self):
        file = open(self.path, 'w')
        for instruction in self.instructions:
            file.writelines(instruction)
        file.close()

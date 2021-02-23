class MachineInstruction:

    def __init__(self, path):
        self.file = open(path, 'w')

    def append_instruction(self, instruction):
        self.file.writelines(instruction)

    @staticmethod
    def coordinate(xyz):
        return f"c {xyz}\n"

    @staticmethod
    def define_routine(id, instructions):
        return [f"R {id}:{len(instructions)}\n"] + instructions

    @staticmethod
    def routine(id):
        return f"r {id}\n"

    @staticmethod
    def special_instruction(id, payload):
        return f"s {id} {payload}\n"

    @staticmethod
    def wait(milliseconds):
        return f"w {milliseconds}\n"

    def close(self):
        self.file.close()

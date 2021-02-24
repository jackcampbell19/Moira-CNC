class MachineInstruction:

    def __init__(self, path):
        self.path = path
        self.instructions = []
        self.defined_routine_count = 0

    def append_instruction(self, instruction):
        if instruction[0] and 'R' in instruction[0]:
            self.defined_routine_count += 1
        self.instructions.append(instruction)

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

    def build(self):
        file = open(self.path, 'w')
        file.writelines([f"D {self.defined_routine_count}\n"])
        for instruction in self.instructions:
            file.writelines(instruction)
        file.close()

import inspect
import os
import sys
cur_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
sys.path.append(f"{cur_dir}/../../../src/preparation/mi")
sys.path.append(f"{cur_dir}/../..")
from Test import Test
from MachineInstruction import MachineInstruction

class MITests(Test):

    name = "mi_test"

    def test_1_create_mi_file(self):
        file_location = f"{cur_dir}/../../runtime/test_1_mi_file.mi"
        mi = MachineInstruction(file_location)
        mi.append_instruction(MachineInstruction.define_routine(0, [MachineInstruction.coordinate('+0,+0,40'), MachineInstruction.coordinate('10,10,50')]))
        mi.append_instruction(MachineInstruction.coordinate('10,25,14'))
        mi.append_instruction(MachineInstruction.coordinate('+0,15,+6'))
        mi.append_instruction(MachineInstruction.coordinate('15,20,25'))
        mi.append_instruction(MachineInstruction.wait(150))
        mi.append_instruction(MachineInstruction.coordinate('-5,+0,+5'))
        mi.append_instruction(MachineInstruction.coordinate('1,2,3'))
        mi.append_instruction(MachineInstruction.routine(0))
        mi.append_instruction(MachineInstruction.coordinate('0,0,-40'))
        mi.append_instruction(MachineInstruction.special_instruction(0, '3,180,50'))
        mi.append_instruction(MachineInstruction.wait(1000))
        mi.build()
        return self.compare_files(file_location, f"{cur_dir}/../../expected/test_1_mi_file_expected.mi")


if __name__ == '__main__':
    MITests().run_tests()

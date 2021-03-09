import inspect
import os
import sys
cur_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
sys.path.append(f"{cur_dir}/../../../src/preparation/mi")
sys.path.append(f"{cur_dir}/../../../src/preparation/interpretation")
sys.path.append(f"{cur_dir}/../..")
from Test import Test
from MachineInstruction import MachineInstruction
from SVGInterpreter import SVGInterpreter

class MITests(Test):

    name = "mi_test"

    def test_1_create_mi_file(self):
        svg_location = f"{cur_dir}/../../files/7-shapes.svg"
        mi_location = f"{cur_dir}/../../runtime/7-shapes.mi"
        interpreter = SVGInterpreter(svg_location)
        interpreter.create_mi(mi_location)
        return True


if __name__ == '__main__':
    MITests().run_tests()

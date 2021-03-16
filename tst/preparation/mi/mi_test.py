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


if __name__ == '__main__':
    MITests().run_tests()

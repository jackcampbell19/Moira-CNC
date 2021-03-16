import inspect
import os
import sys
cur_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
sys.path.append(f"{cur_dir}/../../src/preparation")
sys.path.append(f"{cur_dir}/../../src/preparation/mi")
sys.path.append(f"{cur_dir}/../../src/preparation/interpretation")
sys.path.append(f"{cur_dir}/..")
from Test import Test
from SVGInterpreter import SVGInterpreter
from Simulator import Simulator


class GeneralTest(Test):

    name = "general_test"

    def test_1(self):
        return True


if __name__ == '__main__':
    GeneralTest().run_tests()

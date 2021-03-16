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

    def test_1_create_mi_unverified(self):
        svg_location = f"{cur_dir}/../files/shapes.svg"
        mi_location = f"{cur_dir}/../runtime/shapes.mi"
        interpreter = SVGInterpreter(svg_location)
        interpreter.create_mi(mi_location)
        Simulator(mi_location).run(2)
        return True


if __name__ == '__main__':
    GeneralTest().run_tests()

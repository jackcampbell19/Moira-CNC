import inspect
import os
import sys
cur_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
sys.path.append(f"{cur_dir}/../../../src/preparation/mi")
sys.path.append(f"{cur_dir}/../../../src/preparation/interpretation")
sys.path.append(f"{cur_dir}/../..")
from Test import Test
from SVGInterpreter import SVGInterpreter


class SVGTest(Test):

    name = "mi_test"


if __name__ == '__main__':
    SVGTest().run_tests()

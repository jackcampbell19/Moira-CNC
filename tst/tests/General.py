import inspect
import os
import sys
from os import listdir
from os.path import isfile, join
cur_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
sys.path.append(f"{cur_dir}/../../src/preparation")
sys.path.append(f"{cur_dir}/../../src/preparation/mi")
sys.path.append(f"{cur_dir}/../../src/preparation/interpretation")
sys.path.append(f"{cur_dir}/..")
from Test import Test
from Verification import Verification


class GeneralTest(Test):

    name = "general_test"
    gen_files = f"{cur_dir}/../generated-files"

    def before(self):
        return

    def test_verify_generated_files(self):
        files = [f for f in listdir(self.gen_files) if isfile(join(self.gen_files, f)) and f.endswith('.mi')]
        for f in files:
            if not Verification.verify(join(self.gen_files, f)):
                return False
        return True


if __name__ == '__main__':
    GeneralTest().run_tests()

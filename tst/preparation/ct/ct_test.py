import inspect
import os
import sys
cur_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
sys.path.append(f"{cur_dir}/../../../src/preparation/ct")
sys.path.append(f"{cur_dir}/../..")
from CTXML import CTXML
from CoordinateTrace import CoordinateTrace
from Test import Test

class CTTests(Test):

    name = "ct_test"

    def test_1_create_ctxml_file(self):
        file_location = f"{cur_dir}/../../runtime/test_create_ctxml_file.ctxml"
        ctxml = CTXML(file_location)
        ctxml.define_routine('lift-up', ['+0,+0,40'])
        ctxml.add_coordinate('10,25,14')
        ctxml.add_coordinate('20,-10,+6')
        ctxml.add_coordinate('5,5,5')
        ctxml.add_routine('lift-up')
        ctxml.add_coordinate('10,20,30')
        ctxml.add_coordinate('+0,-1,+1')
        ctxml.close()
        return self.compare_files(file_location, f"{cur_dir}/../../expected/test_create_ctxml_file_expected.ctxml")

    def test_2_convert_ctxml_to_ct(self):
        CoordinateTrace.from_ctxml(f"{cur_dir}/../../runtime/test_create_ctxml_file.ctxml",
                                   f"{cur_dir}/../../runtime/test_convert_ctxml_to_ct.ct")
        return self.compare_files(f"{cur_dir}/../../runtime/test_convert_ctxml_to_ct.ct",
                             f"{cur_dir}/../../expected/test_convert_ctxml_to_ct_expected.ct")


if __name__ == '__main__':
    CTTests().run_tests()

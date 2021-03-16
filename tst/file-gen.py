from os import listdir
from os.path import isfile, join
import inspect
import os
import sys

cur_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
sys.path.append(f"{cur_dir}/../src/preparation/interpretation")

from SVGInterpreter import SVGInterpreter

static_files = f"{cur_dir}/static-files"
gen_files = f"{cur_dir}/generated-files"

files = [f for f in listdir(static_files) if isfile(join(static_files, f)) and f.endswith('.svg')]

for f in files:
    interpreter = SVGInterpreter(join(static_files, f), verbose=True)
    interpreter.create_mi(join(gen_files, f.split('.')[0] + '.mi'))

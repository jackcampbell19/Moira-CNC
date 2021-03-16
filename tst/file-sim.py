from os import listdir
from os.path import isfile, join
import inspect
import os
import sys

cur_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
sys.path.append(f"{cur_dir}/../src/preparation")

from Simulator import Simulator

gen_files = f"{cur_dir}/generated-files"

files = [f for f in listdir(gen_files) if isfile(join(gen_files, f)) and f.endswith('.mi')]

for f in files:
    Simulator(join(gen_files, f)).run(120, verbose=True)

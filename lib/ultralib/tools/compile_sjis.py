#!/usr/bin/env python3

import sys, os
from shiftjis_conv import sjis_process

os.chdir("../../")
WORKING_DIR = os.getcwd()

fb = []
original_c_file = [i for i in sys.argv if ".c" in i][0]
CC = [i for i in sys.argv if "-D__CC=" in i][0][7:]

output_c_file = original_c_file

sys.argv[sys.argv.index(original_c_file)] = output_c_file

original_c_file = "src/voice/" + original_c_file

with open(original_c_file) as f:
	fb = f.read()

os.chdir("build/src/voice")

with open(output_c_file, "w+") as outf:
	sjis_process(fb, outf)

os.system("%s %s" % (CC, " ".join(sys.argv[1:])))

import argparse
import subprocess
import png
import struct

parser=argparse.ArgumentParser(description="Converts extracted textures from png into inc.c files to be linked into the ROM.")
parser.add_argument("input")
parser.add_argument("output")
args=parser.parse_args()

reader = png.Reader(filename=args.input)
width, height, rows, info = reader.read()
rowIndex: int = 0
outputData: bytearray = bytearray()

for row in rows:
    if rowIndex % 2 == 0:
        # odd row, just copy as is
        outputData.extend(row)
    else:
        # even row, swap groups of 8 pixels, or 64 bits
        for swapBlock in struct.iter_unpack(">QQ", row):
            outputData.extend(struct.pack(">QQ", swapBlock[1], swapBlock[0]))

    rowIndex += 1

newPngPath = args.output[:-14] + "_swapped.png"
output = open(newPngPath, 'wb')
writer = png.Writer(width, height, **info)
writer.write_array(output, outputData)
output.close()

# use pigment64 to convert it to .inc.c
subprocess.run(["tools/pigment64/pigment64", "to-bin", "-f", "ci4", "--c-array", "-o", args.output, newPngPath])

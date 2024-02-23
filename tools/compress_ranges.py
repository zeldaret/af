#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import itertools
from pathlib import Path
import sys
import yaml


QUIET = False

def printVerbose(*args, **kwargs):
    if QUIET:
        return
    print(*args, **kwargs)


def ranges(i):
    for _, b in itertools.groupby(enumerate(i), lambda pair: pair[1] - pair[0]):
        b = list(b)
        yield b[0][1], b[-1][1]


def getCompressedSegmentIndices(yamlPath: Path):
    printVerbose("Finding compressed segments...")
    with yamlPath.open() as f:
        yamlObj = yaml.load(f, Loader=yaml.SafeLoader)

    indices = []
    currentIndex = 0
    for segment in yamlObj["segments"]:
        if not isinstance(segment, dict):
            continue

        notInDma = segment.get("notdma", False)
        if notInDma:
            continue

        shouldCompress = segment.get("compress", False)
        if shouldCompress:
            indices.append(currentIndex)
        currentIndex += 1
    return list(ranges(indices))


def main():
    # Args from command line
    parser = argparse.ArgumentParser(description="Compress ROM")

    parser.add_argument("yaml", help="Path to the yaml file", type=Path)
    parser.add_argument('-o', '--outfile', help='output file to write to. None for stdout')

    args = parser.parse_args()

    compressed_ranges = getCompressedSegmentIndices(args.yaml)
    indicesList = []
    for start, end in compressed_ranges:
        if start != end:
            indicesList.append(f"{start}-{end}")
        else:
            indicesList.append(f"{start}")

    if args.outfile is None:
        sys.stdout.write(','.join(indicesList))
        sys.stdout.write("\n")
    else:
        with open(args.outfile, "w") as f:
            f.write(','.join(indicesList))
            f.write("\n")

    return 0


if __name__ == "__main__":
    exit(main())

#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import itertools
from pathlib import Path
import spimdisasm
import subprocess
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
            break
        # print(segment)
        shouldCompress = segment.get("compress", False)
        if shouldCompress:
            indices.append(currentIndex)
        currentIndex += 1
    return list(ranges(indices))


def getDmaStartLen(elfPath: Path) -> tuple[int, int]:
    printVerbose("Retrieving dmadata address...")

    start = -1
    end = -1

    elfFile = spimdisasm.elf32.Elf32File(spimdisasm.common.Utils.readFileAsBytearray(elfPath))

    assert elfFile.symtab is not None, f"Invalid Elf file, it is missing the symtab"
    assert elfFile.strtab is not None, f"Invalid Elf file, it is missing the strtab"

    for entry in elfFile.symtab:
        symName = elfFile.strtab[entry.name]

        if "dmadata_ROM_START" == symName:
            start = entry.value
        elif "dmadata_ROM_END" == symName:
            end = entry.value

    assert start > 0, f"Could not find 'dmadata_ROM_START' in Elf file"
    assert end > 0, f"Could not find 'dmadata_ROM_END' in Elf file"

    return start, (end - start) // 0x10


def main():
    # Args from command line
    parser = argparse.ArgumentParser(description="Compress ROM")

    parser.add_argument("in_rom", help="Uncompressed input ROM filename", type=Path)
    parser.add_argument("out_rom", help="Compressed output ROM filename", type=Path)
    parser.add_argument("elf", help="Path to the uncompressed ROM elf file", type=Path)
    parser.add_argument("yaml", help="Path to the yaml file", type=Path)
    parser.add_argument("--cache", help="Cache directory")
    parser.add_argument("--threads", help="Number of threads to run compression on, 0 disables multithreading", type=int, default=0)
    parser.add_argument("--mb", help="compressed ROM size in MB, default is the smallest multiple of 8mb fitting the whole ROM")
    parser.add_argument("--matching", help="matching compression, forfeits some useful optimizations", action="store_true")
    parser.add_argument("--stderr", help="z64compress will write its output messages to stderr instead of stdout", action="store_true")

    args = parser.parse_args()

    dmaAddr, dmaLen = getDmaStartLen(args.elf)

    compressed_ranges = getCompressedSegmentIndices(args.yaml)
    indicesList = []
    for start, end in compressed_ranges:
        if start != end:
            indicesList.append(f"{start}-{end}")
        else:
            indicesList.append(f"{start}")

    command = f"./tools/z64compress/z64compress "
    command += f"--in {args.in_rom} "
    command += f"--out {args.out_rom} "
    command += f"--codec yaz "
    command += f"--dma 0x{dmaAddr:06X},{dmaLen} "
    command += f"--compress {','.join(indicesList)} "

    if args.matching:
        command += f"--matching "
    if args.mb is not None:
        command += f"--mb {args.mb} "
    if args.cache:
        command += f"--cache {args.cache} "
    if args.threads > 0:
        command += f"--threads {args.threads} "
    if not args.stderr:
        command += f"--only-stdout "


    print(command)

    try:
        subprocess.check_call(command, shell=True)
    except subprocess.CalledProcessError as e:
        # Return the same error code for the wrapper if z64compress fails
        return e.returncode

    return 0


if __name__ == "__main__":
    exit(main())

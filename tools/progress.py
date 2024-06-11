#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path


ASMPATH = Path("asm")
NONMATCHINGS = "nonmatchings"


def getProgressFromMapFile(mapFile: mapfile_parser.MapFile, asmPath: Path, nonmatchings: Path, aliases: dict[str, str]=dict(), pathIndex: int=2) -> tuple[mapfile_parser.ProgressStats, dict[str, mapfile_parser.ProgressStats]]:
    totalStats = mapfile_parser.ProgressStats()
    progressPerFolder: dict[str, mapfile_parser.ProgressStats] = dict()

    for segment in mapFile:
        for file in segment:
            if len(file) == 0:
                continue

            folder = file.filepath.parts[pathIndex]

            if ".a" in folder:
                folder = folder.split('.a')[0]

            if folder in aliases:
                folder = aliases[folder]

            if folder not in progressPerFolder:
                progressPerFolder[folder] = mapfile_parser.ProgressStats()

            originalFilePath = Path(*file.filepath.parts[pathIndex:])

            extensionlessFilePath = originalFilePath
            while extensionlessFilePath.suffix:
                extensionlessFilePath = extensionlessFilePath.with_suffix("")

            fullAsmFile = asmPath / extensionlessFilePath.with_suffix(".s")

            handwrittenAsmFiles = [Path("boot/libc64/fp.o"), Path("makerom/entry.o")]
            
            if originalFilePath in handwrittenAsmFiles:
                wholeFileIsUndecomped = False
            else:
                wholeFileIsUndecomped = fullAsmFile.exists()


            for func in file:
                funcAsmPath = nonmatchings / extensionlessFilePath / f"{func.name}.s"

                symSize = 0
                if func.size is not None:
                    symSize = func.size

                if wholeFileIsUndecomped:
                    totalStats.undecompedSize += symSize
                    progressPerFolder[folder].undecompedSize += symSize
                elif funcAsmPath.exists():
                    totalStats.undecompedSize += symSize
                    progressPerFolder[folder].undecompedSize += symSize
                else:
                    totalStats.decompedSize += symSize
                    progressPerFolder[folder].decompedSize += symSize

    return totalStats, progressPerFolder


def getProgress(mapPath: Path, version: str) -> tuple[mapfile_parser.ProgressStats, dict[str, mapfile_parser.ProgressStats]]:
    mapFile = mapfile_parser.MapFile()
    mapFile.readMapFile(mapPath)

    for segment in mapFile:
        for file in segment:
            if len(file) == 0:
                continue

            filepathParts = list(file.filepath.parts)
            if version in filepathParts:
                filepathParts.remove(version)
            file.filepath = Path(*filepathParts)

    nonMatchingsPath = ASMPATH / version / NONMATCHINGS

    return getProgressFromMapFile(mapFile.filterBySectionType(".text"), ASMPATH / version, nonMatchingsPath, aliases={"ultralib": "libultra"})

def getAssetProgress(mapPath: Path, version: str):
    totalStats = mapfile_parser.ProgressStats()
    progressPerFolder: dict[str, mapfile_parser.ProgressStats] = dict()
    progressPerFolder["objects"] = mapfile_parser.ProgressStats()
    progressPerFolder["unidentified"] = mapfile_parser.ProgressStats()

    mapFile = mapfile_parser.MapFile()
    mapFile.readMapFile(mapPath)
    mapFile = mapFile.filterBySectionType(".data")

    for segment in mapFile:
        for file in segment:

            if len(file) == 0:
                continue

            if str(file.filepath).startswith("build/src/objects"):
                totalStats.decompedSize += file.size
                progressPerFolder["objects"].decompedSize += file.size
            elif str(file.filepath).startswith("build/assets/" + version + "/objects"):
                totalStats.undecompedSize += file.size
                progressPerFolder["objects"].undecompedSize += file.size
            elif str(file.filepath).startswith("build/assets/" + version):
                progressPerFolder["unidentified"].undecompedSize += file.size
                totalStats.undecompedSize += file.size
    
    return totalStats, progressPerFolder

def progressMain():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--version", help="version to process", default="jp")

    args = parser.parse_args()

    mapPath = Path("build") / f"animalforest-{args.version}.map"

    codeTotalStats, codeProgressPerFolder = getProgress(mapPath, args.version)
    assetTotalStats, assetProgressPerFolder = getAssetProgress(mapPath, args.version)
    print("code:")
    mapfile_parser.progress_stats.printStats(codeTotalStats, codeProgressPerFolder)
    print("\n\nassets:")
    mapfile_parser.progress_stats.printStats(assetTotalStats, assetProgressPerFolder)

if __name__ == "__main__":
    progressMain()

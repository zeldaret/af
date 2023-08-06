#!/usr/bin/env python3
import colorama
colorama.init()

import argparse
import collections
import sys
import mapfile_parser
from pathlib import Path


Compared = collections.namedtuple("Compared", [ "buildAddress", "buildFile", "expectedAddress", "expectedFile", "diff"])

def compareMapFiles(mapFileBuild: Path, mapFileExpected: Path) -> tuple[set[mapfile_parser.File], set[mapfile_parser.File], collections.OrderedDict[mapfile_parser.Symbol, Compared]]:
    badFiles = set()
    missingFiles = set()

    print(f"Build mapfile:    {mapFileBuild}", file=sys.stderr)
    print(f"Expected mapfile: {mapFileExpected}", file=sys.stderr)
    print("", file=sys.stderr)

    if not mapFileBuild.exists():
        print(f"{colorama.Fore.LIGHTRED_EX}error{colorama.Fore.RESET}: mapfile not found at {mapFileBuild}. Did you enter the correct path?", file=sys.stderr)
        exit(1)

    if not mapFileExpected.exists():
        print(f"{colorama.Fore.LIGHTRED_EX}error{colorama.Fore.RESET}: expected mapfile not found at {mapFileExpected}. Is 'expected' missing or in a different folder?", file=sys.stderr)
        exit(1)

    buildMap = mapfile_parser.MapFile()
    buildMap.readMapFile(mapFileBuild)
    buildMap = buildMap.filterBySegmentType(".bss")
    expectedMap = mapfile_parser.MapFile()
    expectedMap.readMapFile(mapFileExpected)
    expectedMap = expectedMap.filterBySegmentType(".bss")

    comparedDict = collections.OrderedDict()

    for file in buildMap:
        for symbol in file:
            foundSymInfo = expectedMap.findSymbolByName(symbol.name)
            if foundSymInfo is not None:
                comparedDict[symbol] = Compared( symbol.vram, file, symbol.vram, foundSymInfo.file, symbol.vram - foundSymInfo.symbol.vram )
                if comparedDict[symbol].diff != 0:
                    badFiles.add(file)
            else:
                missingFiles.add(file)
                comparedDict[symbol] = Compared( symbol.vram, file, -1, "", "Unknown" )

    for file in expectedMap:
        for symbol in file:
            foundSymInfo = buildMap.findSymbolByName(symbol.name)
            if foundSymInfo is None:
                missingFiles.add(file)
                comparedDict[symbol] = Compared( -1, "", symbol.vram, file, "Unknown" )

    return badFiles, missingFiles, comparedDict


def printCsv(badFiles, missingFiles, comparedDict, printAll = True):
    print("Symbol Name,Build Address,Build File,Expected Address,Expected File,Difference,GOOD/BAD/MISSING")

    # If it's bad or missing, don't need to do anything special.
    # If it's good, check for if it's in a file with bad or missing stuff, and check if print all is on. If none of these, print it.

    for symbol in comparedDict:
        symbolInfo = comparedDict[symbol]
        symbolGood = colorama.Fore.RED + "BAD" + colorama.Fore.RESET
        if type(symbolInfo.diff) != int:
            symbolGood = colorama.Fore.YELLOW + "MISSING" + colorama.Fore.RESET
            print(f"{symbol.name},{symbolInfo.buildAddress:X},{symbolInfo.buildFile.filepath},{symbolInfo.expectedAddress:X},{symbolInfo.expectedFile.filepath},{symbolInfo.diff},{symbolGood}")
            continue

        if symbolInfo.diff == 0:
            symbolGood = colorama.Fore.GREEN + "GOOD" + colorama.Fore.RESET
            if (not symbolInfo.buildFile in badFiles and not symbolInfo.expectedFile in badFiles) and (not symbolInfo.buildFile in badFiles and not symbolInfo.expectedFile.filepath in badFiles) and not printAll:
                continue

        if symbolInfo.buildFile != symbolInfo.expectedFile:
            symbolGood += colorama.Fore.CYAN + " MOVED" + colorama.Fore.RESET
        print(f"{symbol.name},{symbolInfo.buildAddress:X},{symbolInfo.buildFile.filepath},{symbolInfo.expectedAddress:X},{symbolInfo.expectedFile.filepath},{symbolInfo.diff:X},{symbolGood}")


def main():
    description = "Check that globally visible bss has not been reordered."
    epilog = """\
    N.B. Since this script reads the map files, it can only see globally visible bss; in-function static bss must be examined with other tools.
    """

    parser = argparse.ArgumentParser(description=description, epilog=epilog, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("mapFile", help="Path to a map file.")
    parser.add_argument("mapFileExpected", help="Path to the expected map file. Optional, default is 'expected/mapFile'.", nargs="?", default="")
    parser.add_argument("-a", "--print-all", help="Print all bss, not just non-matching.", action="store_true")
    parser.add_argument("-n", "--no-fun-allowed", help="Remove amusing messages.", action="store_true")
    args = parser.parse_args()

    mapfilePath = Path(args.mapFile)

    if args.mapFileExpected == "":
        mapfileExpectedPath = "expected" / mapfilePath
    else:
        mapfileExpectedPath = Path(args.mapFileExpected)


    badFiles, missingFiles, comparedDict = compareMapFiles(mapfilePath, mapfileExpectedPath)
    printCsv(badFiles, missingFiles, comparedDict, args.print_all)

    if len(badFiles) + len(missingFiles) != 0:
        print("", file=sys.stderr)

        if len(badFiles) != 0:
            print(colorama.Fore.RED + "  BAD" + colorama.Style.RESET_ALL)

            for file in badFiles:
                print(f"bss reordering in {file.filepath}", file=sys.stderr)
            print("", file=sys.stderr)

            if not args.no_fun_allowed:
                print(colorama.Fore.LIGHTWHITE_EX +
                "  BSS is REORDERED!!\n"
                "  Oh! MY GOD!!" 
                + colorama.Style.RESET_ALL, file=sys.stderr)
                print("", file=sys.stderr)

        if len(missingFiles) != 0:
            print(colorama.Fore.YELLOW + "  MISSING" + colorama.Style.RESET_ALL)

            for file in missingFiles:
                print(f"Symbols missing from {file}", file=sys.stderr)
            print("", file=sys.stderr)

            if not args.no_fun_allowed:
                print(colorama.Fore.LIGHTWHITE_EX + "  Error, should (not) be in here " + colorama.Style.RESET_ALL, file=sys.stderr)
                print("", file=sys.stderr)

            print("Some files appear to be missing symbols. Have they been renamed or declared as static? You may need to remake 'expected'", file=sys.stderr)

        return 1

    print("", file=sys.stderr)
    print(colorama.Fore.GREEN + "  GOOD" + colorama.Style.RESET_ALL, file=sys.stderr)

    if args.no_fun_allowed:
        return 0

    print("\n" + colorama.Fore.LIGHTWHITE_EX +
    colorama.Back.RED + "                                  " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + "         CONGRATURATIONS!         " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + "    All Global BSS is correct.    " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + "             THANK YOU!           " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + "      You are great decomper!     " + colorama.Back.RESET + "\n" +
    colorama.Back.RED + "                                  " + colorama.Style.RESET_ALL , file=sys.stderr)

    return 0

if __name__ == "__main__":
    ret = main()
    exit(ret)

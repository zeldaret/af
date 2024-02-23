#!/usr/bin/env python3

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path


def mapToPj64symsMain():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--version", help="version to process", default="jp")
    parser.add_argument("-o", "--output", default="DOUBUTSUNOMORI.sym", type=Path)

    args = parser.parse_args()

    version: str = args.version
    output: Path = args.output
    mapPath = Path("build") / f"animalforest-{version}.map"

    exit(mapfile_parser.frontends.pj64_syms.doPj64Syms(mapPath, output))

if __name__ == "__main__":
    mapToPj64symsMain()

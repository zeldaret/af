#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path

import progress


BASE_URL = "https://progress.deco.mp"
PROJECT = "animalforest"

def uploadProgressMain():
    parser = argparse.ArgumentParser()
    parser.add_argument("version", help="Version slug")
    parser.add_argument("--apikey", help="API key")

    args = parser.parse_args()

    version: str = args.version
    apikey: str = args.apikey
    mapPath = Path("build") / f"animalforest-{args.version}.map"

    codeTotalStats, codeProgressPerFolder = progress.getProgress(mapPath, version)
    codeEntries: dict[str, int] = mapfile_parser.frontends.upload_frogress.getFrogressEntriesFromStats(codeTotalStats, codeProgressPerFolder, verbose=True)

    assetTotalStats, assetProgressPerFolder = progress.getAssetProgress(mapPath, version)
    assetEntries: dict[str, int] = mapfile_parser.frontends.upload_frogress.getFrogressEntriesFromStats(assetTotalStats, assetProgressPerFolder, verbose=True)

    url = mapfile_parser.utils.generateFrogressEndpointUrl(BASE_URL, PROJECT, version)
    mapfile_parser.frontends.upload_frogress.uploadEntriesToFrogress(codeEntries, "code", url, apikey=apikey, verbose=True)
    mapfile_parser.frontends.upload_frogress.uploadEntriesToFrogress(assetEntries, "assets", url, apikey=apikey, verbose=True)

if __name__ == '__main__':
    uploadProgressMain()

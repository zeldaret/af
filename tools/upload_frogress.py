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
    category: str = "code"
    apikey: str = args.apikey
    mapPath = Path("build") / f"animalforest.{args.version}.map"

    totalStats, progressPerFolder = progress.getProgress(mapPath, version)

    entries: dict[str, int] = mapfile_parser.frontends.upload_frogress.getFrogressEntriesFromStats(totalStats, progressPerFolder, verbose=True)

    url = mapfile_parser.utils.generateFrogressEndpointUrl(BASE_URL, PROJECT, version)
    exit(mapfile_parser.frontends.upload_frogress.uploadEntriesToFrogress(entries, category, url, apikey=apikey, verbose=True))

if __name__ == '__main__':
    uploadProgressMain()

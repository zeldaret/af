#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023-2025 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import sys
from pathlib import Path

import decomp_settings
import mapfile_parser


def doThing(
    version: str,
    settings: decomp_settings.Config,
    units: bool,
    sort: bool,
    remaining: bool,
):
    selectedVersion = settings.get_version_by_name(version)
    assert selectedVersion is not None
    mapPath = Path(selectedVersion.paths.map)
    outputPath = Path(selectedVersion.paths.build_dir) / "report.json"

    specificSettings = mapfile_parser.frontends.objdiff_report.SpecificSettings.fromDecompConfig(settings)
    assert specificSettings is not None
    prefixesToTrim = specificSettings.prefixesToTrim
    pathIndex = specificSettings.pathIndex
    assert pathIndex is not None

    reportCategories = mapfile_parser.ReportCategories()
    for cat in specificSettings.categories:
        reportCategories.push(cat.ide, cat.name, cat.paths)

    if specificSettings.checkAsmPaths:
        assert selectedVersion.paths.asm is not None
        asmPath = Path(selectedVersion.paths.asm)
    else:
        asmPath = None

    summaryTableConfig = mapfile_parser.frontends.objdiff_report.SummaryTableConfig(
        doUnits=units,
        sort=sort,
        remaining=remaining,
    )

    exitcode = mapfile_parser.frontends.objdiff_report.doObjdiffReport(
        mapPath,
        outputPath,
        prefixesToTrim,
        reportCategories,
        pathIndex=pathIndex,
        asmPath=asmPath,
        summaryTableConfig=summaryTableConfig,
    )
    sys.exit(exitcode)

def progressMain():
    settings = decomp_settings.scan_for_config()
    versionsChoices = [x.name for x in settings.versions]

    parser = argparse.ArgumentParser(description="Print the progress for each category in your terminal.")
    parser.add_argument("-v", "--version", help="version to process", choices=versionsChoices, default=versionsChoices[0])
    parser.add_argument("-u", "--units", help="Print units instead of categories", action="store_true")
    parser.add_argument("-s", "--sort", help="Sort by decomped size", action="store_true")
    parser.add_argument("-r", "--remaining", help="Print an extra column indicating the remaining percentage to match of each entry", action="store_true")

    args = parser.parse_args()
    version: str = args.version
    units: bool = args.units
    sort: bool = args.sort
    remaining: bool = args.remaining

    doThing(
        version,
        settings,
        units,
        sort,
        remaining,
    )


if __name__ == "__main__":
    progressMain()

#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import dataclasses
from pathlib import Path
import struct


ENTRY_SIZE = 0x8

@dataclasses.dataclass
class ObjectOverlay:
    vromStart: int      # uintptr_t
    vromEnd: int        # uintptr_t

    def rawstr(self) -> str:
        result = f"0x{self.vromStart:08X}, "
        result += f"0x{self.vromEnd:08X}"

        return result

    def isUnset(self) -> bool:
        return self.vromStart == 0 and self.vromEnd == 0

    def _macroEntry_Unset(self, index: int) -> str:
        return f"DEFINE_OBJECT_UNSET(OBJECT_UNSET_{index})"

    def _macroEntry_Normal(self, index: int) -> str:
        return f"DEFINE_OBJECT(object_{self.vromStart:08X}, OBJECT_{index})"

    def macroEntry(self, index: int) -> str:
        if self.isUnset():
            return self._macroEntry_Unset(index)
        return self._macroEntry_Normal(index)

    def renames(self) -> str:
        result = f""

        if self.vromStart != 0:
            result += f'"segment_{self.vromStart:08X}": "object_{self.vromStart:08X}",\n'

        return result


def extractEntry(rom: bytes, offset: int, index: int) -> ObjectOverlay:
    entry = struct.unpack_from(">II", rom, offset + ENTRY_SIZE * index)

    return ObjectOverlay(*entry)


def ExtractActorTableMain():
    parser = argparse.ArgumentParser(description="Object table tool")
    parser.add_argument("rom_path", help="Path to uncompressed rom")
    parser.add_argument("offset", help="Raw offset to the object table. Either dec or hex")
    parser.add_argument("length", help="Amount of entries on the actor table. Either dec or hex")

    parser.add_argument("--renames", help="Print a list of strings to rename instead of the object table", action="store_true")

    args = parser.parse_args()

    rom_path = Path(args.rom_path)
    offset = int(args.offset, 0)
    length = int(args.length, 0)
    renames = args.renames

    with rom_path.open("rb") as f:
        rom = f.read()

    for i in range(length):
        entry = extractEntry(rom, offset, i)

        # print(entry.rawstr())
        # if not entry.isUnset():
        #     if entry.vromStart == entry.vromEnd:
        #         print(entry.rawstr())

        if renames:
            print(entry.renames(), end="")
            pass

        else:
            macroEntry = entry.macroEntry(i)
            print(f"/* 0x{i:03X} */ {macroEntry}")
            pass


if __name__ == '__main__':
    ExtractActorTableMain()


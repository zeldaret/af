#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import dataclasses
from pathlib import Path
import struct


ENTRY_SIZE = 0x20

@dataclasses.dataclass
class ActorOverlay:
    vromStart: int      # uintptr_t
    vromEnd: int        # uintptr_t
    vramStart: int      # void*
    vramEnd: int        # void*
    loadedRamAddr: int  # void*
    initInfo: int       # ActorInit*
    name: int           # char*
    allocType: int      # u16
    numLoaded: int      # s8

    def rawstr(self) -> str:
        result = f"0x{self.vromStart:08X}, "
        result += f"0x{self.vromEnd:08X}, "
        result += f"0x{self.vramStart:08X}, "
        result += f"0x{self.vramEnd:08X}, "
        result += f"0x{self.loadedRamAddr:08X}, "
        result += f"0x{self.initInfo:08X}, "
        result += f"0x{self.name:08X}, "
        result += f"{self.allocType}, "
        result += f"{self.numLoaded}"

        return result

    def allocTypeStr(self) -> str:
        if self.allocType == 0:
            return "ALLOCTYPE_NORMAL"
        if self.allocType == 1:
            return "ALLOCTYPE_ABSOLUTE"
        if self.allocType == 2:
            return "ALLOCTYPE_PERMANENT"
        return "ALLOCTYPE_ERROR"

    def _macroEntry_Unset(self, index: int) -> str:
        return f"DEFINE_ACTOR_UNSET(ACTOR_UNSET_{index})"

    def _macroEntry_Internal(self, index: int) -> str:
        return f"DEFINE_ACTOR_INTERNAL(_{self.vromStart:08X}, ACTOR_{index}, {self.allocTypeStr()})"

    def _macroEntry_Normal(self, index: int) -> str:
        return f"DEFINE_ACTOR(_{self.vromStart:08X}, ACTOR_{index}, {self.allocTypeStr()})"

    def isUnset(self) -> bool:
        return self.initInfo == 0
    def isInternal(self) -> bool:
        return not self.isUnset() and self.vromStart == 0
    def isNormal(self) -> bool:
        if self.isUnset() or self.isInternal():
            return False
        return True

    def macroEntry(self, index: int) -> str:
        if self.isUnset():
            return self._macroEntry_Unset(index)
        elif self.isInternal():
            return self._macroEntry_Internal(index)
        return self._macroEntry_Normal(index)

    def renames(self) -> str:
        result = f""

        if self.initInfo != 0:
            result += f"D_{self.initInfo:08X}_cn,_{self.vromStart:08X}_Profile\n"

        return result


def extractEntry(rom: bytes, offset: int, index: int) -> ActorOverlay:
    entry = struct.unpack_from(">IIIIIIIHb", rom, offset + ENTRY_SIZE * index)

    return ActorOverlay(*entry)


def ExtractActorTableMain():
    parser = argparse.ArgumentParser()
    parser.add_argument("rom_path")
    parser.add_argument("offset")
    parser.add_argument("length")

    args = parser.parse_args()

    rom_path = Path(args.rom_path)
    offset = int(args.offset, 0)
    length = int(args.length, 0)

    with rom_path.open("rb") as f:
        rom = f.read()

    for i in range(length):
        entry = extractEntry(rom, offset, i)
        macroEntry = entry.macroEntry(i)

        print(f"/* 0x{i:02X} */ {macroEntry}")


if __name__ == '__main__':
    ExtractActorTableMain()


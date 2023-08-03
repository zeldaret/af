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
        return f"DEFINE_ACTOR_INTERNAL({self.vromStart:08X}, ACTOR_{index}, {self.allocTypeStr()})"

    def _macroEntry_Normal(self, index: int) -> str:
        return f"DEFINE_ACTOR({self.vromStart:08X}, ACTOR_{index}, {self.allocTypeStr()})"

    def macroEntry(self, index: int) -> str:
        if self.initInfo == 0:
            return self._macroEntry_Unset(index)
        elif self.vromStart == 0:
            return self._macroEntry_Internal(index)
        return self._macroEntry_Normal(index)


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

        print(entry.macroEntry(i))


if __name__ == '__main__':
    ExtractActorTableMain()


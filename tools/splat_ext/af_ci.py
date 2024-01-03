from pathlib import Path
from typing import Optional, TYPE_CHECKING

from util import log

from segtypes.n64.img import N64SegImg

if TYPE_CHECKING:
    from segtypes.n64.palette import N64SegPalette


# Base class for CI4/CI8
class N64SegAf_ci(N64SegImg):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.palette: "Optional[N64SegPalette]" = None
        self.palette_name = args[2]

    def scan(self, rom_bytes: bytes) -> None:
        self.n64img.data = rom_bytes[self.rom_start : self.rom_end]

    def split(self, rom_bytes):
        if self.palette is None:
            # TODO: output with blank palette
            log.error("Palette not found')")
        assert self.palette is not None
        self.palette.extract = False
        self.n64img.palette = self.palette.parse_palette(rom_bytes)

        super().split(rom_bytes)

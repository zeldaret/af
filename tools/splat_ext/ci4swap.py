from typing import TYPE_CHECKING
from splat.util import log, options
from n64img.image import CI4
from splat.segtypes.n64.ci import N64SegCi
import struct

if TYPE_CHECKING:
    from splat.segtypes.n64.palette import N64SegPalette

# CI4 texture but on even rows every 32 bits of data are swapped
class N64SegCi4swap(N64SegCi):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs, img_cls=CI4)

    def split(self, rom_bytes):
        assert self.palettes is not None
        if len(self.palettes) == 0:
            # TODO: output with blank palette
            log.error(
                f"no palettes have been mapped to ci segment `{self.name}`\n(hint: add a palette segment with the same name or use the `palettes:` field of this segment to specify palettes by name')"
            )

        assert isinstance(self.rom_start, int)
        assert isinstance(self.rom_end, int)

        data: bytes = rom_bytes[self.rom_start : self.rom_end]
        rowLength: int = self.width // 2 # in bytes
        outputData:bytearray = bytearray()

        for rowIndex in range(self.height):
            rowStart: int = rowIndex * rowLength
            rowEnd: int = (rowIndex + 1) * rowLength
            rowData: bytes = data[rowStart:rowEnd]

            if rowIndex % 2 == 0:
                # odd row, just copy as is
                outputData.extend(rowData)
            else:
                # even row, swap groups of 32 bits
                for swapBlock in struct.iter_unpack(">II", rowData):
                    outputData.extend(struct.pack(">II", swapBlock[1], swapBlock[0]))

        self.n64img.data = outputData

        for palette in self.palettes:
            path = self.out_path_pal(palette.name)
            path.parent.mkdir(parents=True, exist_ok=True)

            self.n64img.palette = palette.parse_palette(rom_bytes)
            self.n64img.write(path)

            self.log(f"Wrote {path.name} to {path}")
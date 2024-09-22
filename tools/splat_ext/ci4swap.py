from typing import TYPE_CHECKING
from splat.util import log, options
from n64img.image import CI4
from splat.segtypes.n64.ci import N64SegCi

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

        data = rom_bytes[self.rom_start : self.rom_end]
        self.n64img.data = data
        for palette in self.palettes:
            path = self.out_path_pal(palette.name)
            path.parent.mkdir(parents=True, exist_ok=True)

            self.n64img.palette = palette.parse_palette(rom_bytes)
            self.n64img.write(path)

            self.log(f"Wrote {path.name} to {path}")
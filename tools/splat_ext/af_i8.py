from n64img.image import Image, I8
from splat.util import log, options
from splat.segtypes.n64.segment import N64Segment

class N64SegAf_i8(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml),

        self.width = args[0]
        self.height = args[1]

    def scan(self, rom_bytes: bytes):
        self.n64img: Image = I8(b"", 0, 0)
        self.n64img.width = self.width
        self.n64img.height = self.height
        self.n64img.data = rom_bytes[self.rom_start : self.rom_end]

    def split(self, rom_bytes: bytes):
        path = options.opts.asset_path / self.dir / f"{self.name}.i8.png"
        path.parent.mkdir(parents=True, exist_ok=True)

        self.n64img.write(path)

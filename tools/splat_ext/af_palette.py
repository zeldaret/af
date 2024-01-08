import struct
from splat.util import options, log
from splat.segtypes.common.codesubsegment import CommonSegCodeSubsegment

VALID_SIZES = [0x20, 0x40, 0x80, 0x100, 0x200]

class N64SegAf_palette(CommonSegCodeSubsegment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml),

        self.data_only = isinstance(yaml, dict) and yaml.get("data_only", False)

    def scan(self, rom_bytes: bytes):
        data = rom_bytes[self.rom_start : self.rom_end]
        lines = []

        if len(data) not in VALID_SIZES:
            log.error(f"Error: {self.name} (0x{len(data):X} bytes) is not a valid palette size ({', '.join(hex(s) for s in VALID_SIZES)})")

        if not self.data_only:
            lines.append(options.opts.generated_c_preamble)
            lines.append("")
            lines.append(f"unsigned short {self.name}[] = {{")

        for short in struct.iter_unpack(">H", data):
            lines.append(f"    0x{short[0]:04X},")

        if not self.data_only:
            lines.append("};")

        lines.append("")
        self.file_text = "\n".join(lines)

    def split(self, rom_bytes: bytes):
        path = options.opts.asset_path / self.dir / f"{self.name}.palette.inc.c"

        if self.file_text and path:
            path.parent.mkdir(parents=True, exist_ok=True)
            with open(path, "w", newline="\n") as f:
                f.write(self.file_text)

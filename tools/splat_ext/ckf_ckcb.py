import struct
from typing import Optional
from splat.util import options, log
from splat.segtypes.common.codesubsegment import CommonSegCodeSubsegment

class N64SegCkf_ckcb(CommonSegCodeSubsegment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml),

        self.file_text: Optional[str] = None
        self.data_only = isinstance(yaml, dict) and yaml.get("data_only", False)

    def get_linker_section(self) -> str:
        return ".data"

    def scan(self, rom_bytes: bytes):
        data = rom_bytes[self.rom_start : self.rom_end]
        symbol = self.create_symbol(addr=self.vram_start, in_segment=True, type="data", define=True)
        count = len(data)
        lines = []

        if not self.data_only:
            lines.append(options.opts.generated_c_preamble)
            lines.append("")
            lines.append(f"u8 {symbol.name}[{count}] = {{")

        for byte in struct.iter_unpack(">B", data):
            lines.append(f"    0x{byte[0]:02X},")

        if not self.data_only:
            lines.append("};")

        lines.append("")
        self.file_text = "\n".join(lines)

    def split(self, rom_bytes: bytes):
        path = options.opts.asset_path / self.dir / f"{self.name}.inc.c"

        if self.file_text and path:
            path.parent.mkdir(parents=True, exist_ok=True)
            with open(path, "w", newline="\n") as f:
                f.write(self.file_text)

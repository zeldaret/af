import struct
from typing import Optional
from splat.util import options, log
from splat.segtypes.common.codesubsegment import CommonSegCodeSubsegment

class N64SegEvw_data(CommonSegCodeSubsegment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml),

        self.file_text: Optional[str] = None
        self.data_only = isinstance(yaml, dict) and yaml.get("data_only", False)

    def scan(self, rom_bytes: bytes):
        data = rom_bytes[self.rom_start : self.rom_end]
        symbol = self.create_symbol(addr=self.vram_start, in_segment=True, type="data", define=True)
        count = len(data) // 8
        lines = []

        if (len(data)) % 8 != 0:
            log.error(f"Error: evw_data segment {self.name} length ({len(data)}) is not a multiple of 8!")

        if not self.data_only:
            lines.append(options.opts.generated_c_preamble)
            lines.append("")
            lines.append(f"EvwAnimeData {symbol.name}[{count}] = {{")

        for evwAnimeData in struct.iter_unpack(">bxhI", data):
            segment, type, dataPtr = evwAnimeData

            if dataPtr:
                data_ptr_symbol = self.get_symbol(addr=dataPtr).name
            else:
                data_ptr_symbol = "NULL"

            lines.append(f"    {{ {segment}, {type}, &{data_ptr_symbol} }},")

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

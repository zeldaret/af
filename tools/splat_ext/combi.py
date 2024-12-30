import math
import struct
from typing import Optional
from splat.util import options, log
from splat.segtypes.common.codesubsegment import CommonSegCodeSubsegment

class N64SegCombi(CommonSegCodeSubsegment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml),

        self.file_text: Optional[str] = None
        self.data_only = isinstance(yaml, dict) and yaml.get("data_only", False)

    def scan(self, rom_bytes: bytes):
        data = rom_bytes[self.rom_start : self.rom_end]
        symbol = self.create_symbol(addr=self.vram_start, in_segment=True, type="data", define=True)
        entry_len = 6
        count = len(data) // entry_len
        lines = []

        if (len(data)) % entry_len != 0:
            log.error(f"Error: combi segment {self.name} length ({len(data)}) is not a multiple of {entry_len}!")

        if not self.data_only:
            lines.append(options.opts.generated_c_preamble)
            lines.append("")
            lines.append("// Combination types are used as indices into this table.")
            lines.append("// Combination type can be derived from an acre ID by (acreID >> 2)")
            lines.append("// (the two least significant bits of an acre ID store its height)")
            lines.append(f"FieldMakeComboInfo {symbol.name}[{count}] = {{")

        index_digits = math.ceil(math.log(count, 16))

        for index, FieldMakeComboInfo in enumerate(struct.iter_unpack(">HHBB", data)):
            bgId, fgId, blockType, pad = FieldMakeComboInfo
            lines.append(f"  /* 0x{index:0{index_digits}X} */ {{ 0x{bgId:04X}, 0x{fgId:04X}, 0x{blockType:02X} }},")

        if not self.data_only:
            lines.append(f"}}; // size = 0x{count * 6:X}")
            # lines.append("")
            # lines.append(f"s32 {symbol.name}_number = {count};")

        lines.append("")
        self.file_text = "\n".join(lines)

    def split(self, rom_bytes: bytes):
        path = options.opts.asset_path / self.dir / f"{self.name}.inc.c"

        if self.file_text and path:
            path.parent.mkdir(parents=True, exist_ok=True)
            with open(path, "w", newline="\n") as f:
                f.write(self.file_text)

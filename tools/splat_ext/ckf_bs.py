import struct
from typing import Optional
from splat.util import options, log
from splat.segtypes.common.codesubsegment import CommonSegCodeSubsegment

class N64SegCkf_bs(CommonSegCodeSubsegment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml),

        self.file_text: Optional[str] = None
        self.data_only = isinstance(yaml, dict) and yaml.get("data_only", False)

    def scan(self, rom_bytes: bytes):
        data = rom_bytes[self.rom_start : self.rom_end]
        symbol = self.create_symbol(addr=self.vram_start, in_segment=True, type="data", define=True)
        lines = []

        if (len(data)) != 8:
            log.error(f"Error: ckf_bs segment {self.name} length ({len(data)}) is not 8 bytes!")

        if not self.data_only:
            lines.append(options.opts.generated_c_preamble)
            lines.append("\n")
            lines.append(f"BaseSkeletonR {symbol.name} = ")

        numberOfJoints, numberOfDisplayLists, jointElemTable = struct.unpack(">BBxxI", data)
        jointelemtable_symbol = self.get_symbol(addr=jointElemTable).name
        lines.append(f"{{ {numberOfJoints}, {numberOfDisplayLists}, {jointelemtable_symbol} }}")

        if not self.data_only:
            lines.append(";")

        lines.append("\n")
        self.file_text = "".join(lines)

    def split(self, rom_bytes: bytes):
        path = options.opts.asset_path / self.dir / f"{self.name}.inc.c"
        
        if self.file_text and path:
            path.parent.mkdir(parents=True, exist_ok=True)
            with open(path, "w", newline="\n") as f:
                f.write(self.file_text)

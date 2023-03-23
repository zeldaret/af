#!/usr/bin/env python3
from typing import Any, Dict, Optional
import json
import logging
import subprocess
import tempfile
import pathlib
import sys
import queue

import asm_differ.diff as asm_differ

MAX_FUNC_SIZE_LINES = 5000

class AsmDifferWrapper:
    @staticmethod
    def create_config(arch: asm_differ.ArchSettings) -> asm_differ.Config:
        return asm_differ.Config(
            arch=arch,
            # Build/objdump options
            diff_obj=True,
            make=False,
            source_old_binutils=True,
            diff_section=".text",
            inlines=False,
            max_function_size_lines=MAX_FUNC_SIZE_LINES,
            max_function_size_bytes=MAX_FUNC_SIZE_LINES * 4,
            # Display options
            formatter=asm_differ.AnsiFormatter(column_width=50),
            threeway=None,
            base_shift=0,
            skip_lines=0,
            compress=None,
            show_branches=True,
            show_line_numbers=False,
            show_source=False,
            stop_jrra=False,
            ignore_large_imms=False,
            ignore_addr_diffs=False,
            algorithm="levenshtein",
        )

    @staticmethod
    def run_objdump(target_data: bytes, config: asm_differ.Config, label: Optional[str]) -> Optional[str]:
        flags = [
            "--disassemble",
            "--disassemble-zeroes",
            "--line-numbers",
            "--reloc",
        ]

        with tempfile.TemporaryDirectory() as tempdir:
            target_path = pathlib.Path(tempdir) / "out.s"
            target_path.write_bytes(target_data)

            start_addr = 0

            if label:
                nm_command = "mips-linux-gnu-nm"

                if nm_command:
                    try:
                        nm_proc = subprocess.run(
                            [nm_command] + [target_path],
                            capture_output=True,
                            universal_newlines=True
                        )
                    except subprocess.CalledProcessError as e:
                        logger.error(f"Error running nm: {e}")
                        logger.error(e.stderr)

                    if nm_proc.stdout:
                        for line in nm_proc.stdout.splitlines():
                            if label in line:
                                start_addr = int(line.split()[0], 16)
                                break
                else:
                    # logger.error(f"No nm command for {platform}")
                    return None

            flags.append(f"--start-address={start_addr}")

            objdump_command = "mips-linux-gnu-objdump"
            cmds = [objdump_command] + config.arch.arch_flags + flags + [target_path]

            try:
                objdump_proc = subprocess.run(
                    [objdump_command] + config.arch.arch_flags + flags + [target_path],
                    capture_output=True,
                    universal_newlines=True
                )
            except subprocess.CalledProcessError as e:
                # logger.error(e)
                # logger.error(e.stderr)
                return None

        out = objdump_proc.stdout
        return out

    @staticmethod
    def diff(target_elf: bytes, compiled_elf: bytes, diff_label:Optional[str]) -> Dict[str, Any]:
        arch = asm_differ.get_arch("mips")

        config = AsmDifferWrapper.create_config(arch)

        # Base
        if len(target_elf) == 0:
            print("Base asm empty")
            return

        basedump = AsmDifferWrapper.run_objdump(target_elf, config, diff_label)
        if not basedump:
            print("Error running asm-differ on basedump")
            return

        if len(compiled_elf) == 0:
            print("Creation of compilation elf_object failed")
            return

        mydump = AsmDifferWrapper.run_objdump(compiled_elf, config, diff_label)
        if not mydump:
            print("Error running asm-differ")
            return

        # Preprocess the dumps
        basedump = asm_differ.preprocess_objdump_out(None, target_elf, basedump, config)
        mydump = asm_differ.preprocess_objdump_out(None, compiled_elf, mydump, config)

        try:
            display = asm_differ.Display(basedump, mydump, config)
        except Exception:
            print("Error running asm-differ")
            return

        # Print the output
        display.run_sync()

if __name__ == "__main__":
    if len(sys.argv) != 3 and len(sys.argv) != 4:
        print(f"Usage: {sys.argv[0]} [path/to/target.o] [path/to/compiled.o] [function name (optional)]")
        sys.exit(0)
    target = pathlib.Path(sys.argv[1])
    compiled = pathlib.Path(sys.argv[2])
    if len(sys.argv) == 4:
        label = sys.argv[3]
    else:
        label = None
    target_bytes = target.read_bytes()
    compiled_bytes = compiled.read_bytes()
    AsmDifferWrapper.diff(target_bytes, compiled_bytes, label)

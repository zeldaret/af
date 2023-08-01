#!/usr/bin/env python3
#
#   ar
#

from genericpath import isfile
import os, struct, time
from dataclasses import dataclass
from libelf import ElfFile, SB_GLOBAL, SHN_UND

class Archive:
    @dataclass
    class ArchiveFileRecord:
        """
        AR file headers +  data

        Offset  Length  Name                                        Format
        0       16      File identifier                             ASCII
        16      12      File modification timestamp (in seconds)    Decimal
        28      6       Owner ID                                    Decimal
        34      6       Group ID                                    Decimal
        40      8       File mode (type and permission)             Octal
        48      10      File size in bytes                          Decimal
        58      2       Ending characters                           0x60 0x0A
        """
        name : str
        time : int
        uid : int
        gid : int
        mode : int
        size : int
        data : bytes

    def __init__(self):
        self.files = [] # List[ArchiveFileRecord]
        self.armap_entries = None
        self.time = int(time.time())

    def add_data(self, name, time, uid, gid, mode, size, data):
        self.files.append(Archive.ArchiveFileRecord(name, time, uid, gid, mode, size, data))

    def add_file(self, file_path):
        if not os.path.isfile(file_path):
            print(f"Error: No file named {file_path}")
            return

        st = os.stat(file_path)
        name = os.path.basename(file_path)
        time = int(st.st_mtime)
        uid = st.st_uid
        gid = st.st_gid
        mode = st.st_mode
        size = st.st_size

        data = None
        with open(file_path, "rb") as infile:
            data = bytes(infile.read())

        self.add_data(name, time, uid, gid, mode, size, data)

    def add_ar(self, file_path):
        for file in Archive.from_file(file_path).files:
            self.add_data(file)

    def build_image(self):
        def add_bin(ba, bin):
            for b in bin:
                ba.append(b)

        def add_str(ba, s, pad_to_len=-1):
            if pad_to_len != -1:
                s = f"{s:{pad_to_len}}"
            s = s.encode("ASCII")
            for c in s:
                ba.append(c)

        def add_pad(ba):
            if len(ba) % 2 != 0:
                ba.append(0)

        def add_ar_hdr(ba, name, time, uid, gid, mode, length):
            add_str(ba, name, 16)
            add_str(ba, str(time), 12)
            add_str(ba, str(uid), 6)
            add_str(ba, str(gid), 6)
            add_str(ba, oct(mode)[2:], 8)
            add_str(ba, str(length), 10)
            add_str(ba, "`\n")

        b = bytearray()

        # MAGIC

        add_str(b, "!<arch>\n")

        # ARMAP

        armap_data= bytearray()

        armap_entries_files = []

        num_entries = 0
        armap_size = 4
        armap_string_data = bytearray()
        for i,file in enumerate(self.files):
            elf = ElfFile(file.data)
            if elf.symtab is not None:
                for sym in elf.symtab.symbol_entries:
                    if sym.st_shndx != SHN_UND and sym.bind == SB_GLOBAL:
                        num_entries += 1
                        armap_size += 4 + len(sym.name) + 1
                        armap_string_data.extend(sym.name.encode("latin1") + b'\0')
                        armap_entries_files.append(i)

        armap_data.extend(struct.pack(">I", num_entries))
        armap_data.extend([0] * 4 * num_entries) # defer writing file positions until files are emplaced later
        armap_data.extend(armap_string_data)

        if len(armap_data) % 4 != 0:
            alsiz = (len(armap_data) + 3) & ~3
            armap_data.extend([0] * (alsiz - len(armap_data)))

        current_time = int(time.time())

        add_ar_hdr(b, "/", current_time, 0, 0, 0, len(armap_data))
        armap_offsets_start = len(b) + 4
        add_bin(b, armap_data)
        add_pad(b)

        # LONG STRINGS

        long_strings = ""

        file_names = []
        flag = False
        for _,file in enumerate(self.files):
            if len(file.name) >= 16:
                fname = f"{file.name}/\n"
                ind = len(long_strings)
                long_strings += fname
            else:
                fname = f"{file.name}/"
                ind = None
            file_names.append((fname, ind))

            # Weird hack
            if len(long_strings) != 0 and not flag:
                flag = True
                long_strings += "/\n"

        long_strings += "/"

        add_ar_hdr(b, "//", current_time, 0, 0, 0, len(long_strings))
        add_str(b, long_strings)
        add_pad(b)

        # FILES

        armap_pos = 0
        for i,(file,(fname,ind)) in enumerate(zip(self.files, file_names)):
            file_pos = len(b)
            add_ar_hdr(b, f"/{ind}" if ind is not None else fname, file.time, file.uid, file.gid, file.mode, file.size)
            add_bin(b, file.data)
            add_pad(b)

            # Patch the armap with file locations
            while armap_pos < len(armap_entries_files) and armap_entries_files[armap_pos] == i:
                b[armap_offsets_start+armap_pos*4:armap_offsets_start+armap_pos*4+4] = struct.pack(">I", file_pos)
                armap_pos += 1

        return b

    def write(self, file_path):
        ar = self.build_image()
        with open(file_path, "wb") as outfile:
            outfile.write(ar)

    @staticmethod
    def from_image(ar_data):
        long_strings = None
        ar = Archive()

        assert ar_data[:8].decode("ASCII") == "!<arch>\n" , "Not an archive file? Bad file magic value"

        i = 8
        while i < len(ar_data):
            file_name =     ar_data[i:][ 0:][:16].decode("ASCII").strip()
            file_time = int(ar_data[i:][16:][:12].decode("ASCII").strip())
            file_uid  = int(ar_data[i:][28:][: 6].decode("ASCII").strip())
            file_gid  = int(ar_data[i:][34:][: 6].decode("ASCII").strip())
            file_mode = int(ar_data[i:][40:][: 8].decode("ASCII").strip(), 8)
            file_size = int(ar_data[i:][48:][:10].decode("ASCII").strip())
            end = ar_data[i:][58:][:2].decode("ASCII")
            assert end == "`\n"

            data = ar_data[i:][60:][:file_size]
            assert len(data) == file_size

            if file_name == '/':
                """
                "armap"
                The special filename "/" denotes that this entry contains a symbol lookup table used by some libraries
                to speed up file access.
                The symbol table is comprised of three contiguous parts:
                 - A 32-bit Big Endian integer recording the number of symbol entries.
                 - A list of 32-bit Big Endian integers for each symbol entry, recording the position within the
                   archive of the header of the file containing the symbol.
                 - A list of null-terminated strings, the symbol names for each symbol entry.

                We rebuild this from scratch on write out.
                """
                ar.time = file_time
                assert file_uid == 0
                assert file_gid == 0
                assert file_mode == 0

                # Code to interpret the armap, currently unused
                """
                armap_n_syms = struct.unpack(">I", data[0:4])[0]
                offsets = [i[0] for i in struct.iter_unpack(">I", data[4:4+4*armap_n_syms])]

                strings = []
                ofs = 4 + 4 * armap_n_syms
                for _ in range(armap_n_syms):
                    to = data.find(b'\0', ofs)
                    assert to != -1
                    string = data[ofs:to].decode('latin1')
                    strings.append(string)
                    ofs += len(string) + 1
                assert all([b == 0 for b in data[ofs:]])
                assert len(strings) == len(offsets)

                ar.armap_entries = list(zip(offsets, strings))
                """
            elif file_name == '//':
                """
                Long string table. Strings larger than 16 are placed here and referenced from the header by /<offset>.

                We rebuild this from scratch on write out.
                """
                assert file_time == ar.time
                assert file_uid == 0
                assert file_gid == 0
                assert file_mode == 0
                long_strings = data.decode("ASCII")
            else:
                """
                Normal files.
                """
                if file_name.startswith("/"):
                    assert long_strings is not None
                    # Fetch the name from the long string table
                    file_name = long_strings[int(file_name[1:]):].split("\n")[0]
                # Add file
                ar.add_data(file_name[:-1], file_time, file_uid, file_gid, file_mode, file_size, data)

            if file_size % 2 != 0:
                file_size += 1
            i += 60 + file_size

        return ar

    @staticmethod
    def from_file(file_path):
        ar_file = None
        with open(file_path, "rb") as infile:
            ar_file = infile.read()

        return Archive.from_image(ar_file)

def ar_usage(progname):
    print(f"Usage: {progname} [-]{{dmpqrstx}}[abcDfilMNoOPsSTuvV] [member-name] [count] archive-file file...")
    print(f" commands:")
    print(f"  d            - delete file(s) from the archive")
    print(f"  m[ab]        - move file(s) in the archive")
    print(f"  p            - print file(s) found in the archive")
    print(f"  q[f]         - quick append file(s) to the archive")
    print(f"  r[ab][f][u]  - replace existing or insert new file(s) into the archive")
    print(f"  s            - act as ranlib")
    print(f"  t[O][v]      - display contents of the archive")
    print(f"  x[o]         - extract file(s) from the archive")
    print(f" command specific modifiers:")
    print(f"  [a]          - put file(s) after [member-name]")
    print(f"  [b]          - put file(s) before [member-name] (same as [i])")
    print(f"  [D]          - use zero for timestamps and uids/gids (default)")
    print(f"  [U]          - use actual timestamps and uids/gids")
    print(f"  [N]          - use instance [count] of name")
    print(f"  [f]          - truncate inserted file names")
    print(f"  [P]          - use full path names when matching")
    print(f"  [o]          - preserve original dates")
    print(f"  [O]          - display offsets of files in the archive")
    print(f"  [u]          - only replace files that are newer than current archive contents")
    print(f" generic modifiers:")
    print(f"  [c]          - do not warn if the library had to be created")
    print(f"  [s]          - create an archive index (cf. ranlib)")
    print(f"  [S]          - do not build a symbol table")
    print(f"  [v]          - be verbose")
    print(f"  [V]          - display the version number")
    print(f"  @<file>      - read options from <file>")
    print(f"  --output=DIRNAME - specify the output directory for extraction operations")
    return 1

def ar(argv):
    if len(argv) < 2:
        return ar_usage(argv[0])

    progname = argv[0]
    create_ok = False
    make_ar_idx = False
    no_symtab = False
    verbose = False

    def verbose_print(msg):
        if verbose:
            print(msg)

    def dcmd(modifiers, args):
        if modifiers != "":
            print(f"{progname}: bad modifiers -- '{modifiers}'")
            return ar_usage(progname)

        ar_file = args[0]
        o_files = args[1:]

        ar = Archive.from_file(ar_file)
        for file in ar.files:
            if file.name in o_files:
                ar.files.remove(file)
        ar.write(ar_file)
        return 0

    def mcmd(modifiers, args):
        print("<UNIMPLEMENTED>")
        return 1

    def pcmd(modifiers, args):
        if modifiers != "":
            print(f"{progname}: bad modifiers -- '{modifiers}'")
            return ar_usage(progname)
        if len(args) != 1:
            print(f"{progname} p: bad args")
            return ar_usage(progname)

        ar_file = args[0]

        ar = Archive.from_file(ar_file)
        for file in ar.files:
            print(file.data)
        return 0

    def qcmd(modifiers, args):
        print("<UNIMPLEMENTED>")
        return 1

    def rcmd(modifiers, args):
        if modifiers !="":
            print("<UNIMPLEMENTED MODIFIERS>")
        if len(args) < 2:
            print(f"{progname} r: bad args")
            return ar_usage(progname)

        ar_file = args[0]
        o_files = args[1:]

        ar = Archive()
        if os.path.isfile(ar_file):
            ar = Archive.from_file(ar_file)
        else:
            if not create_ok:
                print(f"Warning: Created  file {ar_file}")
            ar = Archive()

        for o_file in o_files:
            ar.add_file(o_file)

        ar.write(ar_file)

    def scmd(modifiers, args):
        print("<UNIMPLEMENTED>")
        return 1

    def tcmd(modifiers, args):
        # TODO modifiers

        if len(args) != 1:
            print(f"{progname} t: bad args")
            return ar_usage(progname)

        ar_file = args[0]

        ar = Archive.from_file(ar_file)
        for file in ar.files:
            print(file.name)
        return 0

    def xcmd(modifiers, args):
        if modifiers not in ('', 'o'):
            print(f"{progname}: bad modifiers -- '{modifiers}'")
            return ar_usage(progname)
        if len(args) not in (1, 3) or not (args[0].startswith("--output") or args[1].startswith("--output")):
            print(f"{progname} t: bad args")
            return ar_usage(progname)

        original_times = modifiers == 'o'

        if args[0].startswith("--output"):
            out_dir = args[1]
            ar_file = args[2]
        elif args[1].startswith("--output"):
            out_dir = args[2]
            ar_file = args[0]
        else:
            ar_file = args[0]
            out_dir = ""

        # Create dir if not exists
        if not os.path.exists(out_dir):
            os.makedirs(out_dir, exist_ok=True)

        if not os.path.isdir(out_dir):
            print(f"Output directory {out_dir} is a file")
            return ar_usage(progname)

        # Extract files to destination
        ar = Archive.from_file(ar_file)
        for file in ar.files:
            opath =os.path.join(out_dir, file.name)
            with open(opath, "wb") as ofile:
                ofile.write(file.data)

            if not original_times:
                t = time.time()
                os.utime(opath, (t, t))
            # TODO patch with original dates etc.

        return 0

    argtbl = {
        'd': dcmd, #            delete file(s) from the archive
        'm': mcmd, # [ab]       move file(s) in the archive
        'p': pcmd, #            print file(s) found in the archive
        'q': qcmd, # [f]        quick append file(s) to the archive
        'r': rcmd, # [ab][f][u] replace existing or insert new file(s) into the archive
        's': scmd, #            act as ranlib
        't': tcmd, # [O][v]     display contents of the archive
        'x': xcmd, # [o]        extract file(s) from the archive
    }

    arg1 = argv[1]
    if arg1[0] == '-':
        arg1 = arg1[1:]
    cmd = arg1[0]

    if cmd not in argtbl:
        print(f"{progname}: invalid option -- '{cmd}'")
        return ar_usage(argv[0])

    modifiers = arg1[1:]

    create_ok = "c" in modifiers
    modifiers = modifiers.replace("c","")
    make_ar_idx = "s" in modifiers
    modifiers = modifiers.replace("s","")
    no_symtab = "S" in modifiers
    modifiers = modifiers.replace("S","")
    verbose = "v" in modifiers
    modifiers = modifiers.replace("v","")

    if "V" in modifiers:
        print(f"{progname} v1.0")

    return argtbl[cmd](modifiers, argv[2:])

if __name__ == '__main__':
    import sys
    sys.exit(ar(sys.argv))

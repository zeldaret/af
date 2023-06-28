#!/usr/bin/env python3
#
#   Patch metadata in .ar files
#

import argparse

def ar_patch(ar, original, new_uid, new_gid, new_filemode):
    """
    AR file headers

    Offset  Length  Name                                        Format
    0       16      File identifier                             ASCII
    16      12      File modification timestamp (in seconds)    Decimal
    28      6       Owner ID                                    Decimal
    34      6       Group ID                                    Decimal
    40      8       File mode (type and permission)             Octal
    48      10      File size in bytes                          Decimal
    58      2       Ending characters                           0x60 0x0A
    """
    assert len(ar) > 0x24 , "Got empty archive?"

    armap_time1 = None
    armap_time2 = None

    i = 8
    while i < len(original):
        file_name = original[i:][0:][:16].decode("ASCII")
        file_size = int(original[i:][48:][:10].decode("ASCII").strip())
        end = original[i:][58:][:2].decode("ASCII")

        assert end == "`\n"

        if file_name.strip() == "/":
            armap_time1 = original[i+16:i+16+12]
        elif file_name.strip() == "//":
            armap_time2 = original[i+16:i+16+12]

        if file_size % 2 != 0:
            file_size += 1
        i += file_size + 60

    assert armap_time1 is not None
    assert armap_time2 is not None

    i = 8
    while i < len(ar):
        file_name = ar[i:][0:][:16].decode("ASCII")
        file_size = int(ar[i:][48:][:10].decode("ASCII").strip())
        end = ar[i:][58:][:2].decode("ASCII")

        assert end == "`\n"

        if file_name.strip() == "/":
            ar[i+16:i+16+12] = armap_time1
        elif file_name.strip() == "//":
            ar[i+16:i+16+12] = armap_time2
        else:
            ar[i+28:i+28+6] = f"{new_uid:<6}".encode("ASCII")[:6]
            ar[i+34:i+34+6] = f"{new_gid:<6}".encode("ASCII")[:6]
            ar[i+40:i+40+8] = f"{new_filemode:<8}".encode("ASCII")[:8]

        if file_size % 2 != 0:
            file_size += 1
        i += file_size + 60

def main():
    parser = argparse.ArgumentParser(description="Patch metadata in .a files.")
    parser.add_argument("target", help="path to the ar file to patch")
    parser.add_argument("original", help="path to the original ar file")
    parser.add_argument("uid", help="new uid")
    parser.add_argument("gid", help="new gid")
    parser.add_argument("filemode", help="new filemode")
    args = parser.parse_args()

    ar = None
    with open(args.target, "rb") as ar_file:
        ar = bytearray(ar_file.read())

    original = None
    with open(args.original, "rb") as original_ar_file:
        original = bytearray(original_ar_file.read())

    ar_patch(ar, original, args.uid, args.gid, args.filemode)

    with open(args.target, "wb") as ar_file:
        ar_file.write(ar)

if __name__ == '__main__':
    main()

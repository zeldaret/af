#!/bin/bash
set -e

# This script should only be used when we need to modify the accepted amount of warnings.

DIR="$(dirname "$(readlink -f "$0")")"
cd "$DIR/../.."

make distclean
make WERROR=0 setup 2> tools/warnings_count/warnings_setup_current.txt
make WERROR=0 lib 2> tools/warnings_count/warnings_lib_current.txt
make WERROR=0 extract 2> tools/warnings_count/warnings_extract_current.txt
make WERROR=0 uncompressed 2> tools/warnings_count/warnings_uncompressed_current.txt
make WERROR=0 compressed 2> tools/warnings_count/warnings_compress_current.txt

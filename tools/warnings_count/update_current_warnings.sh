#!/bin/bash
set -e

# This script should only be used when we need to modify the accepted amount of warnings.

DIR="$(dirname "$(readlink -f "$0")")"
cd "$DIR/../.."

make distclean
make WERROR=0 WARNINGS_CHECK=1 setup 2> tools/warnings_count/warnings_setup_current.txt
make WERROR=0 WARNINGS_CHECK=1 lib 2> tools/warnings_count/warnings_lib_current.txt
make WERROR=0 WARNINGS_CHECK=1 extract 2> tools/warnings_count/warnings_extract_current.txt
make WERROR=0 WARNINGS_CHECK=1 rom 2> tools/warnings_count/warnings_build_current.txt
make WERROR=0 WARNINGS_CHECK=1 compress 2> tools/warnings_count/warnings_compress_current.txt

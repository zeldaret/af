#!/usr/bin/bash

cd $1

mkdir -p .cmp

for f in *.o ;
do
    ${CROSS}objcopy -p --strip-debug $f .cmp/${f/.o/.cmp.o}
done

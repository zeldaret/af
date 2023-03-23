#!/usr/bin/bash

for file in $(find src -name *.c)
do
    mv ${file} ${file%.c}._c
done

for file in $(find src -name *.s)
do
    mv ${file} ${file%.s}._s
done

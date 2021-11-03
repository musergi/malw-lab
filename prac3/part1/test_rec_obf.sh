#!/bin/bash

IDA_PATH=~/ida-freeware/ida64

nasm -felf64 shell.asm -o shell.asm.o
ld shell.asm.o -o shell.asm.bin
rm shell.asm.o
objdump -d shell.asm.bin | python3 embed_into_placeholder.py > tmp.asm
rm shell.asm.bin
nasm -felf64 tmp.asm -o tmp.asm.o
ld tmp.asm.o -o tmp.asm.bin
rm tmp.asm.o
$IDA_PATH tmp.asm.bin
rm tmp.asm.bin

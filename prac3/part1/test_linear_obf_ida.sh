#!/bin/bash

IDA_PATH=~/ida-freeware/ida64

nasm -felf64 shell_linear_obf.asm -o shell_linear_obf.asm.o
ld shell_linear_obf.asm.o -o shell_linear_obf.asm.bin
rm shell_linear_obf.asm.o
$IDA_PATH shell_linear_obf.asm.bin
rm shell_linear_obf.asm.bin

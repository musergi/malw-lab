#!/bin/bash
EXPLOITABLE=exploitable
GCC_FLAGS="-m32 -z execstack -fno-stack-protector -mpreferred-stack-boundary=2"


sysctl -w kernel.randomize_va_space=0
gcc $GCC_FLAGS $EXPLOITABLE.c -o $EXPLOITABLE
gdb ./$EXPLOITABLE
sysctl -w kernel.randomize_va_space=1

#!/bin/bash

sysctl -w kernel.randomize_va_space=0
./exploitable $(python3 exploit.py)
sysctl -w kernel.randomize_va_space=1

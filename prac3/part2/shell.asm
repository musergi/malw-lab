section .text

global _start

_start:
    mov rdi, 1
    mov rsi, 0x0a6f6c6c6548 
    mov rdx, 6
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall

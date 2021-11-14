section .text
    global _start
_start:
    jmp short ender
starter:
    mov rax, 1
    mov rdi, 1
    pop rsi
    mov rdx, 6
    syscall
    mov rax, 60
    xor rdi, rdi
    syscall
ender:
    call starter ; call pushes to the stack address of first byte of db
    db "Virus", 10
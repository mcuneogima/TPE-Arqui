GLOBAL write
GLOBAL read

section .test

write:
    mov rax, 4
    int 80h
    ret

read:
    mov 
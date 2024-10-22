GLOBAL write
GLOBAL read
GLOBAL sleep

section .text

write:
    mov rax, 1
    int 80h
    ret

read:
    mov rax, 0
    int 80h
    ret
    

sleep:
    mov rax, 35;
    int 80h
    ret
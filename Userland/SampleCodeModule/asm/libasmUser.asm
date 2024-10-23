GLOBAL write
GLOBAL read
GLOBAL sleep
; GLOBAL devolverRegistros
; EXTERN printRegistros

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

; devolverRegistros:
;    mov [registros],rax
;    mov rax,registros
;    add rax, 8
;    mov [rax], rbx
;    add rax, 8


;    call printRegistros 
;    ret

section .bss
registros resq 10
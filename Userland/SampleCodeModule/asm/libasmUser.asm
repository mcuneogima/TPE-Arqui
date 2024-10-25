GLOBAL write
GLOBAL read
GLOBAL sleep
GLOBAL zoom
GLOBAL draw
GLOBAL screenDetails
GLOBAL setCursor
; GLOBAL devolverRegistros
; EXTERN printRegistros

section .text

write:
    push rbp
    mov rbp,rsp
    mov rax, 1
    int 80h
    mov rsp, rbp
    pop rbp
    ret

read:
    push rbp
    mov rbp,rsp

    mov rax, 0
    int 80h
    
    mov rsp, rbp
    pop rbp
    ret
    

sleep:
    push rbp
    mov rbp,rsp
    mov rax, 35;
    int 80h
    mov rsp, rbp
    pop rbp
    ret

zoom:
    push rbp
    mov rbp, rsp
    mov rax, 28
    int 80h
    mov rsp, rbp
    pop rbp
    ret

draw:
    push rbp
    mov rbp, rsp
    mov rax, 43 ;franco colapinto
    int 80h
    mov rsp, rbp
    pop rbp
    ret

screenDetails:
    push rbp
    mov rbp, rsp
    mov rax, 44
    int 80h
    mov rsp, rbp
    pop rbp
    ret

setCursor:
    push rbp
    mov rbp, rsp
    mov rax, 45
    int 80h
    mov rsp, rbp
    pop rbp
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

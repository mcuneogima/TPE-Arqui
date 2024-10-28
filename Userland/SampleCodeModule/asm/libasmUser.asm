GLOBAL write
GLOBAL read
GLOBAL sleep
GLOBAL zoom
GLOBAL draw
GLOBAL screenDetails
GLOBAL setCursor
GLOBAL devolverRegistros
GLOBAL clockTime
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

devolverRegistros:
    mov [registros],rax
    mov rax,registros
    add rax, 8
;    mov rbx, 7Ah
    mov [rax], rbx
    add rax, 8
    mov [rax], rcx
    add rax, 8
    mov [rax], rdx
    add rax, 8
    mov [rax], rsi
    add rax, 8
    mov [rax], rdi
    add rax, 8
    mov [rax], rbp
    add rax, 8
    mov [rax], rsp
    add rax, 8
    mov [rax], r8
    add rax, 8
    mov [rax], r9
    mov rax, registros
    ; call printRegistros
    ret

clockTime:
    push rbp
    mov rbp, rsp
    mov rax, 46
    int 80h
    mov rsp, rbp
    pop rbp
    ret


section .bss
registros resq 10

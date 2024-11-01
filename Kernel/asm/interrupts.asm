
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _irq60Handler

GLOBAL _exception0Handler
GLOBAL _exception6Handler

GLOBAL esc_pressed
GLOBAL get_regs



EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallDispatcher

EXTERN getStackBase
EXTERN printRegistros



SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState
	mov byte [regs_save], 0
	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	cmp byte [regs_save], 1
	jne .fin
	mov [registros],rax
    mov rax,registros
    add rax, 8
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
	add rax, 8
	mov rdi, [rsp] ;RIP
	mov [rax], rdi
	add rax,8
	mov rdi,[rsp+8] ;CS
	mov [rax],rdi
	add rax,8
	mov rdi,[rsp+8*2] ;RFLAGS
	mov [rax],rdi
.fin:
	iretq
%endmacro



%macro exceptionHandler 1
	push rdi
	mov [registros],rax
    mov rax,registros
    add rax, 8
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
	add rax, 8
	mov rbx, [rsp+8] ;RIP
	mov [rax], rbx
	add rax,8
	mov rbx,[rsp+8*2] ;CS
	mov [rax],rbx
	add rax,8
	mov rbx,[rsp+8*3] ;RFLAGS
	mov [rax],rbx

    mov rdi, registros
	call printRegistros
	pop rdi
	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher
	call getStackBase
	mov [rsp+8*3], rax
	mov rax, userLand
	mov [rsp], rax 
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

_irq60Handler:
	pushState
	
	mov r9, r8
	mov r8, rcx
	mov rcx, rdx
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, rax
	call syscallDispatcher

	popState
	iretq

;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

_exception6Handler:
	exceptionHandler 6


haltcpu:
	cli
	hlt
	ret

esc_pressed:
	mov byte [regs_save], 1
	ret

get_regs:
	mov rax, registros
	ret


SECTION .data
userLand equ 0x400000

SECTION .bss
	aux resq 1
	registros resq 13
	regs_save resb 0

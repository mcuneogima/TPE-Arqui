GLOBAL cpuVendor
GLOBAL getSeconds
GLOBAL getMinutes
GLOBAL getHours
GLOBAL getDoW
GLOBAL getMonth
GLOBAL getYear
GLOBAL returnKBOutputInterrupt
section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

returnKBOutputInterrupt:
	push rbp
	mov rbp,rsp

	in al, 60h

	mov rsp, rbp
	pop rbp
	ret


getSeconds:
	push rbp
	mov rbp, rsp

	mov al, 0
	out 70h, al
	in al,71h

	mov rsp, rbp
	pop rbp
	ret

getMinutes:
	push rbp
	mov rbp, rsp

	mov al, 2
	out 70h, al
	in al,71h

	mov rsp, rbp
	pop rbp
	ret

getHours:
	push rbp
	mov rbp, rsp

	mov al, 4
	out 70h, al
	in al,71h

	mov rsp, rbp
	pop rbp
	ret

getDoW:
	push rbp
	mov rbp, rsp

	mov al, 7
	out 70h, al
	in al,71h

	mov rsp, rbp
	pop rbp
	ret

getMonth:
	push rbp
	mov rbp, rsp

	mov al, 8
	out 70h, al
	in al,71h

	mov rsp, rbp
	pop rbp
	ret

getYear:
	push rbp
	mov rbp, rsp

	mov al, 9
	out 70h, al
	in al,71h

	mov rsp, rbp
	pop rbp
	ret

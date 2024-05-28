GLOBAL cpuVendor
GLOBAL getKey

GLOBAL get_sec
GLOBAL get_min
GLOBAL get_hour
GLOBAL save_registers
EXTERN copy_registers
GLOBAL beep
GLOBAL stop_beep

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


getKey:
	push rbp
    mov rbp, rsp

    xor rax, rax
    in al, 60h

    mov rsp, rbp
    pop rbp
    ret

get_sec:
	push rbp
	mov  rbp,rsp
	mov al, 0
	out 70h, al
	in al, 71h
	mov rsp,rbp
	pop rbp
	ret

get_min:
	push rbp
	mov  rbp,rsp
	mov al, 2
	out 70h, al
	in al, 71h
	mov rsp,rbp
	pop rbp
	ret


get_hour:
	push rbp
	mov  rbp,rsp
	mov rax,0
	mov al, 4
	out 70h, al
	in al, 71h
	mov rsp,rbp
	pop rbp
	ret

save_registers:
    mov rdi, rbp 
    call copy_registers
    ret

beep:
	;no funciona

stop_beep:
  	in al, 61h
	and al, 0xFC
	out 61h, al
  	ret

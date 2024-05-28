GLOBAL cpuVendor
GLOBAL getKey

GLOBAL get_sec
GLOBAL get_min
GLOBAL get_hour
GLOBAL beep
GLOBAL stop_beep

GLOBAL get_regs_snap
;vectores
GLOBAL regs

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

beep:
	push rbp
    push rdx
	mov rbp, rsp

	mov al, 0xB6
	out 43h, al

    mov rdx, 0
    mov rax, 1193180
    div rdi
    
	out 42h, al
	mov al, ah
	out 42h, al

	in al, 61h
 	or al, 03h
	out 61h, al

	mov rsp, rbp
    pop rdx
	pop rbp
	ret

stop_beep:
  	in al, 61h
	and al, 0xFC
	out 61h, al
  	ret


get_regs_snap:
	; guardamos los registros en este orden: 
	;RAX, RBX, RCX, RDX, RSI, RDI, RBP, R8, R9, R10, R11, R12, R13
	; R14, R15, RSP,RIP
    mov [regs+8*0],	rax
	mov [regs+8*1],	rbx
	mov [regs+8*2],	rcx
	mov [regs+8*3],	rdx
	mov [regs+8*4],	rsi
	mov [regs+8*5],	rdi
	mov [regs+8*6],	rbp
	mov [regs+8*7], r8
	mov [regs+8*8], r9
	mov [regs+8*9], r10
	mov [regs+8*10], r11
	mov [regs+8*11], r12
	mov [regs+8*12], r13
	mov [regs+8*13], r14
	mov [regs+8*14], r15
	mov [regs+8*15], rsp	;RSP
	mov rax, [rsp]   ; RSP contains the return adress, so we get the RIP
	mov [regs+8*16], rax
	ret


SECTION .bss
	regs resq 17	;registros para el snap
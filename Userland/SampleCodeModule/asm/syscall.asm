GLOBAL write
GLOBAL read

section .txt:

read:
    mov rax, 0
    mov rdi, 0
    int 80h
    ret

write:
    mov rax, 1
    int 80h
    ret
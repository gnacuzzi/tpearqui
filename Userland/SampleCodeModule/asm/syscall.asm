GLOBAL write
GLOBAL read_char
GLOBAL clear_screen
GLOBAL get_seconds
GLOBAL setlettersize
GLOBAL getRegs

read_char:
    mov rax, 0
    ;mov rdi, 0
    int 80h
    ret

write:
    mov rax, 1
    int 80h
    ret

clear_screen:
    mov rax, 2
    int 80h
    ret

get_seconds:
    mov rax, 3
    int 80h
    ret

setlettersize:
    mov rax, 4
    int 80h
    ret

getRegs:
    mov rax, 5
    int 80h
    ret
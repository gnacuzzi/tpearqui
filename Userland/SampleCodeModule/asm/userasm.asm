GLOBAL dividebyzeroexception
GLOBAL invalidoperationexception

dividebyzeroexception:
    mov raz, 0
    div rax
    ret

invalidoperationexception:
	db	0xFF, 0xFF    ;chequear esto
    ret
#include <stdint.h>
#include <videoDriver.h>
#include <keyboard.h>


#define STDIN 0
#define STDOUT 1
#define STDERR 2


#define READ 0
#define WRITE 1
#define CLEAR 2

static void syscall_write(uint32_t fd, char c);
static void syscall_read( uint64_t buffer);
static void syscall_clear();



uint64_t syscallDispatcher(uint64_t nr, uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5) {
	switch (nr) {
        case READ:
        //hay algo que no me convence, puede llegar a fallar
            syscall_read(arg0);
		case WRITE:
			syscall_write((uint32_t)arg0, (char)arg1);
            break;
        case CLEAR:
            syscall_clear();
            break;
	}
	return 0;
}


static void syscall_read(uint64_t buffer){
    //estoy asumiendo que siempre leo de entrada estandar
    ((char*) buffer)[0] = nextElement();
}

static void syscall_write(uint32_t fd, char c){
    //Color prevColor = getFontColor();
    if(fd == STDERR)
        //setFontColor(ERROR_COLOR);
        return; //pongo return por ahora porque no tenemos el tema font
    else if(fd != STDOUT)
        return;
    draw_char(c);
    //setFontColor(prevColor);
}

static void syscall_clear(){
    clear_screen();
}

#include <stdint.h>
#include <videoDriver.h>
#include <keyboard.h>
#include <lib.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define READ 0
#define WRITE 1
#define CLEAR 2
#define TIME 3
#define LETTERSIZE 4
#define REGISTERS 5
#define CONTROL 6

static void syscall_write(uint32_t fd, char c);
static void syscall_read( uint64_t buffer);
static void syscall_clear();
static uint32_t syscall_time();
static void syscall_lettersize(int size);
static void syscall_registers(uint64_t * buffer);
static int syscall_control();




uint64_t syscallDispatcher(uint64_t nr, uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5) {
	switch (nr) {
        case READ:
            syscall_read(arg0);
		case WRITE:
			syscall_write((uint32_t)arg0, (char)arg1);
            break;
        case CLEAR:
            syscall_clear();
            break;
        case TIME:
            return syscall_time();
            break;
        case LETTERSIZE:
            syscall_lettersize((int) arg0);
            break;
        case REGISTERS:
            syscall_registers((uint64_t *) arg0);
            break;
        case CONTROL:
            return syscall_control();
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

static uint32_t syscall_time(){
    uint8_t hours, minutes, seconds;
    get_time(&hours, &minutes, &seconds);
    return seconds + minutes * 60 + ((hours + 24 - 3) % 24) * 3600;
}

static void syscall_lettersize(int size){
    set_lettersize(size);
}

static void syscall_registers(uint64_t * buffer){
    uint64_t * snapshot = get_snapshot();
    for(int i = 0; i < REGS; i++)
        buffer[i] = snapshot[i];
    return buffer;
}

static int syscall_control(){
    return get_control();
}
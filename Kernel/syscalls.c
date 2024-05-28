#include <stdint.h>
#include <videoDriver.h>
#include <keyboard.h>
#include <lib.h>
#include <time.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define READ 0
#define WRITE 1
#define CLEAR 2
#define SECONDS 3
#define MINUTES 4
#define HOURS 5
#define LETTERSIZE 6
#define REGISTERS 7
#define CONTROL 8
#define SOUND 9

static void syscall_write(uint32_t fd, char c);
static void syscall_read( uint64_t buffer);
static void syscall_clear();
static void syscall_seconds(uint64_t arg0);
static void syscall_minutes(uint64_t arg0);
static void syscall_hours(uint64_t arg0);
static void syscall_lettersize(int size);
static void syscall_registers(uint64_t * buffer);
static int syscall_control();
static void make_sound(uint64_t freq, uint64_t time);




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
        case SECONDS:
            syscall_seconds(arg0);
            break;
        case MINUTES:
            syscall_minutes(arg0);
            break;
        case HOURS:
            syscall_hours(arg0);
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
        case SOUND:
            make_sound(arg0, arg1);
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
/*
static uint32_t syscall_time(){
    uint8_t hours, minutes, seconds;
    get_time(&hours, &minutes, &seconds);
    return seconds + minutes * 60 + ((hours + 24 - 3) % 24) * 3600;
}
*/

static void syscall_seconds(uint64_t sec){
    *((int *)sec) = get_sec();
}

static void syscall_minutes(uint64_t min){
    *((int *)min) = get_min();
}

static void syscall_hours(uint64_t hour){
    *((int *)hour) = get_hour();
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

static void make_sound(uint64_t freq, uint64_t tick){
    uint32_t div = 1193180 / freq;
    if(freq > 0){
        beep((uint8_t)div);
    }
    int initial_ticks = ticks_elapsed();
    while(ticks_elapsed() - initial_ticks < tick){
        _hlt();
    }
    if(freq > 0)
        stop_beep();
}
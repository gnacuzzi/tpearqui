#include <stdint.h>
#include <videoDriver.h>


#define STDIN 0
#define STDOUT 1


#define WRITE 1

static void syscall_write(uint64_t x, uint64_t y, uint64_t c, uint64_t fd, uint64_t r5);

//esta hay que programarla en assembler pero tengo sueño me parece mejor la idea de pachu que la de david
//pero por ahora la dejo asi porque me duele la cabeza
uint64_t syscallDispatcher(uint64_t nr, uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5) {
	//completar
    return 0;
}

// no termino de entender quien llamaria a este
static void syscall_write(uint64_t x, uint64_t y, uint64_t c, uint64_t color, uint64_t r5){
    draw_string(x, y, (char *) c, WHITE);
}

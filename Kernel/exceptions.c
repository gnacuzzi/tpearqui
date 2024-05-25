#include <videoDriver.h>
#include <lib.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_ID 6

zero_division(uint64_t * rip, uint64_t * rsp);
invalid_op_code( uint64_t * rip, uint64_t * rsp);

static char * _regNames[] = {"RAX", "RBX", "RCX", "RDX", "RBP", "RDI", "RSI", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"};

void print_regs(uint64_t rip, uint64_t rsp, uint64_t * newRsp) {
	//creo que itoa hace cualquier cosa
	char buffer[100];
	draw_string("RIP: ");
	//draw_string(int_to_string(rip, buffer, 10));
	draw_string("\n");
	draw_string("RSP: ");
	//draw_string(int_to_string(rsp, buffer, 10));
	draw_string("\n");
	for (int i = 0; i < sizeof(_regNames)/sizeof(char *); i++){
		draw_string(_regNames[i]);
		draw_char(':');
		draw_char(' ');
		//draw_string(int_to_string(newRsp[i], buffer, 10));
		draw_char('\n');
	}
}

void exceptionDispatcher(int exception, uint64_t * rip, uint64_t * rsp) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division(rip,  rsp);
	} else if (exception == INVALID_OP_CODE_ID){
		invalid_op_code( rip, rsp);
	}
}

zero_division(uint64_t * rip, uint64_t * rsp) {
	draw_string("\nerror: se lanzo una excepcion de division por zero\n");
	draw_char('\n');
	print_regs(rip, *rsp, rsp - 4);
	draw_string("\nse reiniciara la consola");
	draw_char('\n');
	draw_char('\n');
}

invalid_op_code( uint64_t * rip, uint64_t * rsp) {
	draw_string("\nerror: se lanzo una excepcion de operacion invalida\n");
	print_regs(rip, *rsp, rsp - 4);
	draw_string("\nse reiniciara la consola");
	draw_char('\n');
	draw_char('\n');
}
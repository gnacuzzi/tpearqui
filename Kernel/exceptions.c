#include <videoDriver.h>
#include <lib.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_ID 6

zero_division(uint64_t rip, uint64_t * rsp);
invalid_op_code( uint64_t rip, uint64_t * rsp);

static char * _regNames[] = {"RAX", "RBX", "RCX", "RDX", "RBP", "RDI", "RSI", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"};

//hasta aca lo agregado
void print_regs(uint64_t rip, uint64_t rsp, uint64_t * newRsp) {
	printf("RIP: 0x%x\nRSP: 0x%x\n", rip, rsp);
    for (int i = 0; i < sizeof(_regNames)/sizeof(char *); i++)
        printf("%s: 0x%x\n", _regNames[i], *(newRsp - i));
}

void exceptionDispatcher(int exception, uint64_t * rip, uint64_t * rsp) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division(rip,  rsp);
	} else if (exception == INVALID_OP_CODE_ID){
		invalid_op_code( rip, rsp);
	}
}

zero_division(uint64_t rip, uint64_t * rsp) {
	draw_string("\nerror: se lanzo una excepcion de division por zero\n");
	draw_char('\n');
	print_regs(rip, *rsp, rsp - 4);
	draw_string("\nse reiniciara la consola");
	draw_char('\n');
	draw_char('\n');
}

invalid_op_code( uint64_t rip, uint64_t * rsp) {
	draw_string("\nerror: se lanzo una excepcion de operacion invalida\n");
	print_regs(rip, *rsp, rsp - 4);
	draw_string("\nse reiniciara la consola");
	draw_char('\n');
	draw_char('\n');
}
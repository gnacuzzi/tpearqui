#include <videoDriver.h>
#include <lib.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_ID 6

zero_division();
invalid_op_code();


uint64_t reg_snap[REGS] = {0};      /* Vector de valores de registros */
static char * regs[] = {"RAX","RBX","RCX","RDX","RSI","RDI","RBP","R8","R9","R10","R11","R12","R13","R14","R15", "RSP","RIP"};
extern const uint64_t exceptregs[17];

//hasta aca lo agregado
void print_regs() {
	for (int i = 0; i<REGS; i++){
		printf("%s: 0x%x\n", regs[i], exceptregs[i]);
    }
}

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division();
	} else if (exception == INVALID_OP_CODE_ID){
		invalid_op_code();
	}
}

zero_division() {
	draw_string("\nerror: se lanzo una excepcion de division por zero\n");
	draw_char('\n');
	print_regs();
	draw_string("\nse reiniciara la consola");
	draw_char('\n');
	draw_char('\n');
}

invalid_op_code() {
	draw_string("\nerror: se lanzo una excepcion de operacion invalida\n");
	print_regs();
	draw_string("\nse reiniciara la consola");
	draw_char('\n');
	draw_char('\n');
}
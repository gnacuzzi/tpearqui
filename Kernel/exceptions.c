#include <videoDriver.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_ID 6

static void zero_division();
static void invalid_op_code();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division();
	} else if (exception == INVALID_OP_CODE_ID){
		invalid_op_code();
	}
}

static void zero_division() {
	draw_string("\nerror: se lanzo una excepcion de division por zero\n");
	//print_regs();
	draw_string("\nse reiniciara la consola");
	draw_char('\n');
	draw_char('\n');
}

void invalid_op_code() {
	draw_string("\nerror: se lanzo una excepcion de operacion invalida\n");
	//print_regs();
	draw_string("\nse reiniciara la consola");
	draw_char('\n');
	draw_char('\n');
}

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
	//clearScreen();
	//draw_string(400, 50, "TUVISTE UNA ZERO DIVISION", 25, RED, BLACK);
	//printRegs(); //programar
	//clearScreen();
}

void invalid_op_code() {
	//clearScreen();
	//draw_string(400, 50, "TUVISTE UNA OP-CODE", 19, RED, BLACK);
	//printRegs();
	//clearScreen();
}
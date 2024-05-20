
#define ZERO_EXCEPTION_ID 0

static void zero_division();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
}

static void zero_division() {
	clearScreen();
	//draw_string(400, 50, "TUVISTE UNA ZERO DIVISION", 25, RED, BLACK);
	//printRegs(); //programar
	clearScreen();
}
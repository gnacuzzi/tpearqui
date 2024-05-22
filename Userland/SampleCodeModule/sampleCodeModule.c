#include <stdio.h> 
//#include <userasm.h>

#define BUFFER_LENGTH 20
#define MAX_PARAMETERS 1  //todavia no sabemos cuantos parametros se van a enviar como maximo
#define PARAMETERS_LENGTH 20
/*
static const char* allCommands[] = {"dividebyzero", "eliminator", "help", "invalidoperation","lettersize", "time"};
static void (*commandsFunction[])(char *parameters) = {dividebyzero, eliminator, help, invalidoperation, lettersize, time}; //funciones a hacer

static void dividebyzero(char** parameters){
	if(parameters != 0){
		printf("DivideByZero doesn't need parameters\n");
		return;
	}

	dividebyzeroexception();
}

static void eliminator(char** parameters){
	//completar
}

static void invalidoperation(char** parameters){
	if(parameters != 0){
		printf("InvalidOperation doesn't need parameters\n");
		return;
	}

	invalidoperationexception();
}

static void lettersize(char** parameters){
	//completar
}

static void time(char** parameters){
	//completar
}	


static void help(char** parameters){
	if(parameters != 0){
		printf("Help doesn't need parameters\n");
		return;
	}

	const char* manual=
	"DIVIDEBYZERO				Command to verify the exception routine \"Divide by zero\"\n"
	"ELIMINATOR					Challenge yourself or you and a friend to an elimination game\n"
	"HELP						Display a menu with all the available commands in StarShell\n"
	"INVALIDOPERATION			Command to verify the exception routine \"Invalid Opcode\"\n"
	"LETTERSIZE					Change the letter size to your preferences\n"
	"TIME						Show current time\n";
	printf(manual);
}

void scanCommand(char* command, char **parameters, char* buffer){
	// buffer = "command arg1 arg2"
	int i, j ,k;

	for(i=0, j=0; buffer[i] != " "; i++ ){
		command[j++] = buffer[i];
	}

	command[j] = 0;

	while (buffer[i] == " "){
		i++;
	}
	
	for(j=0, k=0; buffer[i] != "0"; i++){
		if(buffer[i] != " "){
			parameters[j][k++] = buffer[i];
		}
		else{
			parameters[j][k]=0;
			j++;
			k=0;
			while (buffer[i] == " "){
				i++;
			}
		}
	}

}

int commandId(char* command){
	char *aux = command;
	for(int i=0; command[i]!=0; i++){
		int cmp = strcmp(aux, allCommands[i]);
		if(cmp < 0){ //ordenado alfabeticamente
			return -1;
		}
		else{
			return i;
		}
	}
	return -1;
}
*/

int main() {
	/*
	clear();
	printf("Wellcome to StarShell! Write which module you want to use. To see ours modules write help\n");


	while(1){
		printf("~$ ");
		char buf[BUFFER_LENGTH] = {0};
		scanf(buf, BUFFER_LENGTH);

		char command[BUFFER_LENGTH] = {0};
		char parameters[MAX_PARAMETERS][PARAMETERS_LENGTH] = {{0}}; //arreglo de arreglo de chars para cada parametro
		scanCommand(command, parameters, buf);

		int id = commandId(command);
		if(id >= 0){
			commandsFunction[id](parameters);
		}
		else{
			printf(command);
			printf(": invalid command\n");
		}
	}
	*/
	return 0;
}
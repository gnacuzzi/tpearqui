//#include <userasm.h>

#include "include/libc.h"
#include "include/userasm.h"
#include "include/syscall.h"
#include "include/eliminator.h"


#define BUFFER_LENGTH 256
#define MAX_PARAMETERS 2  //todavia no sabemos cuantos parametros se van a enviar como maximo
#define PARAMETERS_LENGTH 256


static void dividebyzero(char** parameters, int cantParams){
	if(cantParams != 0){
		printf("DivideByZero doesn't need parameters\n");
		return;
	}
	dividebyzeroexception();
}

static void eliminator(char** parameters, int cantParams){
	if(cantParams != 0){
		printf("Eliminator doesn't need parameters\n");
		return;
	}
	start_eliminator();
}

static void invalidoperation(char** parameters, int cantParams){
	if(cantParams != 0){
		printf("InvalidOperation doesn't need parameters\n");
		return;
	}

	invalidoperationexception();
}

static void lettersize(char** parameters, int cantParams){
	if(cantParams != 1){
		printf("You must insert ONE parameter indicating the letter size you desire\n");
	}else if (parameters[0] > 5 || parameters[0] < 1)
	{
		printf("The letter size must be a number between 1 and 5\n");
	}else{
		setlettersize(parameters[0]);	
	}
	return;
}

static void time(char** parameters, int cantParams){
	if(cantParams != 0){
		printf("time doesn't need parameters\n");
		return;
	}
	uint32_t seconds = get_seconds();
    uint32_t h = seconds / 3600, m = seconds % 3600 / 60, s = seconds % 3600 % 60;
	printf("Current time is:\n");
    printf("%d:%d:%d\r\n", h, m, s);
	//creo que no me funciona el printf o devuelvo mal
}	

static void clear(char** parameters, int cantParams){
	if(cantParams != 0){
		printf("Clear doesn't need parameters\n");
		return;
	}
	clearscreen();
}

static void help(char** parameters, int cantParams){
	if(cantParams != 0){
		printf("Help doesn't need parameters\n");
		return;
	}

	const char* manual=
	"DIVIDEBYZERo               Command to verify the exception routine \"Divide by zero\"\n"
	"ELIMINATOR                 Challenge yourself or you and a friend to an elimination game\n"
	"HELP                       Display a menu with all the available commands in StarShell\n"
	"INVALIDOPERATION           Command to verify the exception routine \"Invalid Opcode\"\n"
	"LETTERSIZE                 Change the letter size to your preferences\n"
	"TIME                       Show current time\n"
	"CLEAR                      Clears the screen\n";
	printf(manual);
}

static const char* allCommands[] = {"CLEAR", "DIVIDEBYZERO", "ELIMINATOR", "HELP", "INVALIDOPERATION","LETTERSIZE", "TIME"};
static void (*commandsFunction[])(char ** parameters, int cantParams) = {clear, dividebyzero, eliminator, help, invalidoperation, lettersize, time}; //funciones a hacer

int scanCommand(char* command, char parameters[MAX_PARAMETERS][PARAMETERS_LENGTH], char* buffer){
	// buffer = "command arg1 arg2"
	int i, j ,k;


	for(i=0, j=0; buffer[i] != ' ' && buffer[i] != 0; i++, j++ ){
		command[j] = buffer[i];
	}

	command[j] = 0;

	if(buffer[i] == 0){
		return 0;
	}

	while (buffer[i] == ' '){
		i++;
	}
	
	int toReturn=1;

	for(j=0, k=0; buffer[i] != 0;){
		if(buffer[i] != ' '){
			if(!isNumber(buffer[i])){
				parameters[j][k++] = buffer[i++];
			}else{
				parameters[j][k++] = (buffer[i++]-'0');		//lo paso de su ascii
			}
		}
		else{
			parameters[j][k]=0;
			k=0;
			j++;
			toReturn++;
			while (buffer[i] == ' '){
				i++;
			}
		}
	}
	return toReturn;
}

int commandId(char* command){
	char *aux = command;
	for(int i=0; allCommands[i]!=0 ; i++){
		int cmp = strcmp(aux, allCommands[i]);
		if(cmp < 0){ //ordenado alfabeticamente
			return -1;
		}
		else if(cmp == 0){
			return i;
		}
	}
	return -1;
}


int main() {
	//clearscreen(); //lo saque porque sino no se me imprimia la excepcion
	printf("Wellcome to StarShell! Write which module you want to use. To see ours modules write help\n");
	printf("~$");

	char buffer[BUFFER_LENGTH] = {0}; 
	int idx = 0;

	while(1){
        char c  = readchar();
        
        if (c != -1 && c!= 0){
            if(c == '\b'){
                if(idx > 0){ 
                	putchar(c);
                    idx--;
                }
            }else if(c == '\n'){ 
                printf("\n");
                buffer[idx] = 0;
				if(buffer[0] != 0){
					char command[BUFFER_LENGTH]={0};
					char params[MAX_PARAMETERS][PARAMETERS_LENGTH]={{0}};
					int cantParams = scanCommand(command, params,buffer);
					int id;
					if((id = commandId(command))>=0) {
						commandsFunction[id](params, cantParams);
					}
					else {
						printf(command);
						printf(": command not found\n");
					}
					for(int i=0; buffer[i]!=0; i++){		//vaciamos el buffer
						buffer[i]=0;
					}
					idx=0;
				}
                printf("~$");
            } else if(c != '\t'){
                buffer[idx++] = c;
                putchar(c);
            }
        
        }
	}
	return 0;
}
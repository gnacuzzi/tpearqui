#include <stdint.h>
#include "include/libc.h"

static int CANT_PLAYERS=1;
static int SPEED=1;
static int LEVEL=4;

#define ESC '\x1B'
#define ENTER '\n'
#define SPACEBAR ' '


#define MSG_START "ELIMINATOR (ARQUI'S VERSION)\n PLAYERS:%d \n SPEED: %d \n LEVEL: %d \n\n [SPACE] to begin game \n [ENTER] to change \n [ESCAPE] to exit \n"
#define MSG_SPEED "SPEED (1-10): "
#define MSG_PLAYERS "PLAYERS (1-2): "
#define MSG_LEVEL "LEVEL (1-4)"


typedef struct{
    uint16_t x, y;
    uint16_t velocity;
    uint8_t points;
} Player;

void start_eliminator(){
    clearscreen();
    printf(MSG_START, CANT_PLAYERS, SPEED, LEVEL);
    char input;
    while((input = readchar()) != SPACEBAR && input != ENTER){
        if(input == ESC){
            return;
        }
    }
    if(input == SPACEBAR){
        play();
    }else{
        settings();
    }
}

void settings(){
    char input;
    printf(SPEED);
    input = readchar();
    if(input<1 || )
}
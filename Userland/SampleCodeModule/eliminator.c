#include <stdint.h>
#include "include/libc.h"
#include "include/eliminator.h"

static int CANT_PLAYERS= 1;
static int SPEED= 1;
static int LEVEL= 4;

#define ESC '\x1B'
#define ENTER '\n'
#define SPACEBAR ' '


#define MSG_START "ELIMINATOR (ARQUI'S VERSION)\n PLAYERS:%d \n SPEED: %d \n LEVEL: %d \n\n [SPACE] to begin game \n [ENTER] to change \n [ESCAPE] to exit \n"
#define MSG_SPEED "SPEED (1-9): "
#define MSG_PLAYERS "PLAYERS (1-2): "
#define MSG_LEVEL "LEVEL (1-4): "

#define MSG_P1 "El jugador uno se mueve con las flechas\n"
#define MSG_P2 "El jugador dos se mueve con las WSAD\n"
#define MSG_SINGLE "Muevete usando las flechas\n"


typedef struct{
    uint16_t x, y;
    uint16_t velocity;
    uint8_t points;
    Color color;
    char* name;
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
        starting_screen();
    }else{
        settings();
    }
}

void settings(){
    clearscreen();
    char input;
    printf(MSG_SPEED);
    while((input = readchar()) != ENTER){
        if(input >= '1' && input <= '9'){
            putchar(input);
            SPEED = ctoi(input);
            putchar(ENTER);
        }
    }
    
    printf(MSG_LEVEL);
    while((input = readchar()) != ENTER){
        if(input>='1' && input<='4'){
            putchar(input);
            LEVEL = ctoi(input);
            putchar(ENTER);
        }
    }

    printf(MSG_PLAYERS);
    while((input = readchar()) != ENTER){
        if(input=='1' || input=='2'){
            putchar(input);
            CANT_PLAYERS = ctoi(input);
            putchar(ENTER);    
        }
    }
    if(CANT_PLAYERS == 2){
        char * name={0};
        printf("1st player's name: ");
        scanf(name);
        Player player1 = {0, 0, SPEED, 0, name};
        printf("2nd player's name: ");
        scanf(name);
        Player player2 = {0, 0, SPEED, 0, name};
    }else{
        Player player = {0, 0, SPEED, 0, "single_player"};
    }
    start_eliminator();
}

void starting_screen(){
    clearscreen();
    if(CANT_PLAYERS == 1){
        printf(MSG_SINGLE);
    } else{
        printf(MSG_P1);
        printf(MSG_P2);
    }
    printf("Presione SPACE para jugar o ENTER para volver al menu\n");
    char c;
    while((c= readchar())!=ESC){
        if (c == SPACEBAR){
            play();
        }if( c == ENTER){
            start_eliminator();
        }   
    }
}

void play(){

}
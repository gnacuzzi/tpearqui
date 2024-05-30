#include <stdint.h>
#include "include/libc.h"
#include "include/eliminator.h"
#include "include/syscall.h"

static int CANT_PLAYERS= 1;
static int SPEED= 1;
static int LEVEL= 4;

static char board[SCREEN_WIDTH/SQUARE_SIZE][SCREEN_HEIGHT/SQUARE_SIZE]; //ver tema tamaño

#define OUT_OF_BOUNDS(x, y) ((x) > SCREEN_WIDTH || (x) < 0 || (y) > SCREEN_HEIGHT || (y) < 0) 

Player player1, player2;


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
        }
    }
    putchar(ENTER);

    
    printf(MSG_LEVEL);
    while((input = readchar()) != ENTER){
        if(input>='1' && input<='4'){
            putchar(input);
            LEVEL = ctoi(input);
        }
    }
    putchar(ENTER);

    printf(MSG_PLAYERS);
    while((input = readchar()) != ENTER){
        if(input=='1' || input=='2'){
            putchar(input);
            CANT_PLAYERS = ctoi(input);
        }
    }
    putchar(ENTER);    

    if(CANT_PLAYERS == 2){
        char * name={0};
        printf("1st player's name: ");
        scanf(name);
        player1 = (Player){SCREEN_WIDTH * STARTING_OFFSET_1, SCREEN_HEIGHT/2, 0, 1, 0, PINK, name};
        printf("2nd player's name: ");
        scanf(name);
        player2 = (Player) {SCREEN_WIDTH * STARTING_OFFSET_2, SCREEN_HEIGHT/2, 0, -1, 0, LIGHT_GREEN, name};
    }else{
        player1 = (Player) {SCREEN_WIDTH * STARTING_OFFSET_1, SCREEN_HEIGHT/2, 0, 1, 0, PINK, "You"};
        player2 = (Player) {SCREEN_WIDTH * STARTING_OFFSET_2, SCREEN_HEIGHT/2, 0, -1, 0, LIGHT_GREEN, "Elimnator"};
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
    printf("Click SPACE to play or ENTER to go back to the menu\n");
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
    while (1)
    {
        if(CANT_PLAYERS==1){
            play1();
        }else{
            play2();
        }
        if(!want_continue()){
            break;
        }
    }
    start_eliminator();
}

int want_continue(){
    clear_screen();
    printf(POINTS, player1.name, player1.points, player2.name, player2.points);
    printf("Press [SPACE] to cotinue or [ENTER] to change options or to return");
    int c;
    while (c=readchar() != ENTER)
    {
        if(c==SPACEBAR){
            return 1;
        }
    }
    return 0;    
}

void play1(){
    set_enviroment();
}

void play2(){
    set_enviroment();
    char c;
    while(1){
        c = readchar();
        switch (c){
        case 'W':
            if (player2.inc_y != 1){
                player2.inc_y = -1;
                player2.inc_x = 0;
            }
            break;
        case 'A':
            if (player2.inc_x != 1){
                player2.inc_y = 0;
                player2.inc_x = -1;
            }
            break;
        case 'S':
            if (player2.inc_y != -1){
                player2.inc_y = 1;
                player2.inc_x = 0;
            }
            break;        
        case 'D':
            if (player2.inc_x != -1){
                player2.inc_y = 0;
                player2.inc_x = 1;
            }
            break;
        case 2: // left
            if (player1.inc_x != 1){
                player1.inc_x = -1;
                player1.inc_y = 0;
            }
            break;
        case 3: // right
            if (player1.inc_x != -1){
                player1.inc_x = 1;
                player1.inc_y = 0;
            }
            break;
        case 4: // up
            if (player1.inc_y != 1){
                player1.inc_x = 0;
                player1.inc_y = -1;
            }
            break;        
        case 5: // down
            if (player1.inc_y != -1){
                player1.inc_x = 0;
                player1.inc_y = 1;
            }
            break;  
        }
        //fijarse tema esc

        if(checkWin(player1.x, player1.y, player1.name, player2.x, player2.y, player2.name)==1){
            return;
        }

        board[player1.x/SQUARE_SIZE][player1.y/SQUARE_SIZE] = 1;
        board[player2.x/SQUARE_SIZE][player2.y/SQUARE_SIZE] = 1;

        player1.x += SQUARE_SIZE*player1.inc_x;
        player2.x += SQUARE_SIZE*player2.inc_x;
        player1.y += SQUARE_SIZE*player1.inc_y;
        player2.y += SQUARE_SIZE*player2.inc_y;
        
        draw_rectangle(player1.x, player1.y,SQUARE_SIZE, SQUARE_SIZE, PINK);
        draw_rectangle(player2.x, player2.y, SQUARE_SIZE, SQUARE_SIZE, LIGHT_GREEN);
    }
    clear_screen();
}

int checkWin(uint16_t x1, uint16_t y1, char*  name1, uint16_t x2, uint16_t y2, char*  name2){
    if (board[x1/SQUARE_SIZE][y1/SQUARE_SIZE] == 1 || OUT_OF_BOUNDS(x1,y1)){
        clear_screen();
        printf("%s WINS", name1);
        return 1;
    }else if(board[x2/SQUARE_SIZE][y2/SQUARE_SIZE] == 1 || OUT_OF_BOUNDS(x2,y2)){
        clear_screen();
        printf("%s WINS", name2);
        return 1;
    }else if (x2==x1 && y2==y1){
        clear_screen();
        printf("It's a tie");
        return 1;
    }
    return 0;
}

void set_enviroment(){
    clearscreen();
    for(int i; i < (SCREEN_WIDTH/SQUARE_SIZE); i++){
        for(int j; j<(SCREEN_HEIGHT/SQUARE_SIZE); j++){
            board[i][j] = 0;
        }
    }
    draw_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT * 0.03, RED);
    if(CANT_PLAYERS==2){
        printf(POINTS, player1.name, player1.points, player2.name, player2.points);
    }else{
        //printf(POINTS, player1.points);
    }    
}
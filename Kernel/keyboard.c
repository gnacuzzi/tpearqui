#include <keyboard.h>
#include <stdint.h>

#define BUFFER_CAPACITY 256                             
static int _bufferStart = 0;                
static int _bufferEnd = 0;                    
static int buff[BUFFER_CAPACITY] = {0};  /* Vector ciclico que guarda las teclas 
                                                 * que se van leyendo del teclado */
static const char keyBoardTable[256] =             /* Mapa de scancode a ASCII */
    {   0,  0,  '1',  '2',  '3',  '4',  '5',  '6', '7',  '8',  '9', '0', '-',  '=',  '\b',  ' ',
        'q',  'w',  'e',  'r',  't',  'y',  'u',  'i', 'o',  'p',  '[', ']',  '\n',  0, 'a', 's',
        'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  '\'',  0,  0,  '\\', 'z',  'x', 'c', 'v',
        'b',  'n',  'm',  ',',  '.',  '/',  0,  '*', 0,  ' ',  0, 0, 0,  0, 0, 0};

static int cantElems = 0; 


void keyboard_handler(int tecla){
    if(tecla <=0x79){ // 0x79 because its the code for the biggest 'press'. We do this to avoid getting the releas of a key into the buffer
        
        if (cantElems == BUFFER_CAPACITY){
            return;
        }
        if(_bufferEnd == BUFFER_CAPACITY) _bufferEnd = 0; // Reposition of both the front and rear pointer
        if(_bufferStart == BUFFER_CAPACITY) _bufferStart  = 0;
        buff[_bufferEnd++] = keyBoardTable[tecla];
    
        cantElems++;
    }
}

char nextElement(){ // devuelve el primer elemento del buffer
    if(cantElems <= 0 ) {return -1;} 
    char toRet = buff[_bufferStart];
    _bufferStart++;
    cantElems--;
    return toRet;
}

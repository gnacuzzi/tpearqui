 #include <videoDriver.h>
 #include <keyboard.h>
 #include <lib.h>

 #define BUFFER_SIZE 256
 static const char keyBoardTable[256] = 
    {       
          0,    27,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  
          '9',   '0',   '-',  '=','\b',' ','Q',  'W',  'E',  'R', 
          'T',  'Y',  'U',  'I',   'O',  'P',  '[',   ']',  '\n',    0,    
         'A', 'S','D','F',  'G',  'H',  'J',  'K',  'L',  ';', 
          '\'', 0, 0,  '\\', 'Z', 'X', 'C','V','B','N',
          'M', ',', '.',  '/',  0,  '*',     0,  ' ',    0,     0,  
           0,  0, 0,0,0,0,0,0,0,0,
            0,0,4,0,0,2,0,3,0,0,
            5,0,0,0,0,0,0,0,0,0
            // 2: left arrow
            // 3: right arrow
            // 4: up arrow 
            // 5: down arrow 
    };
static char buff[BUFFER_SIZE] = {0}; //Defining a circular vector that we use as keyboard buffer

static int front = 0; //First iterator. Points to the front of the buffer
static int rear = 0; // Second iterator. Points to the last element added
static int cantElems = 0; 

char nextElement(){ // returns the first element pushed into the buffer in cronological order
    if(cantElems <= 0 ) {return -1;} 
    char toRet = buff[front];
    front++;
    cantElems--;
    return toRet;
}
 
void keyboard_handler(){ // Every time someone presses a key this function gets called and inserts into the circular buffer
    uint8_t tecla = getKey();
    if(tecla <=0x79){ // 0x79 because its the code for the biggest 'press'. We do this to avoid getting the releas of a key into the buffer
        
        if (cantElems == BUFFER_SIZE){
            return;
        }
        if(rear == BUFFER_SIZE) rear = 0; // Reposition of both the front and rear pointer
        if(front == BUFFER_SIZE) front  = 0;
        buff[rear++] = keyBoardTable[tecla];
        cantElems++;
    }
}
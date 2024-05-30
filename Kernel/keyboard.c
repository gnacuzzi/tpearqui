 #include <videoDriver.h>
 #include <keyboard.h>
 #include <lib.h>

 #define BUFFER_SIZE 256
 
int get_control();
int control = 0;

static const char keyboard_matrix[256] = 
    {       
          0,    27,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  
          '9',   '0',   '-',  '=',8,' ','Q',  'W',  'E',  'R', 
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

static int first = 0; //First iterator. Points to the front of the buffer
static int last = 0; // Second iterator. Points to the last element added
static int cant_elems = 0; 

char next(){ // returns the first element pushed into the buffer in cronological order
    if(cant_elems <= 0 ) {return -1;} 
    char out = buff[first];
    first++;
    cant_elems--;
    return out;
}
 
void keyboard_handler(){ // Every time someone presses a key this function gets called and inserts into the circular buffer
    uint8_t key = get_key();
    if(key <=0x79){ // 0x79 because its the code for the biggest 'press'. We do this to avoid getting the releas of a key into the buffer
        if (key == 29) {
            control = 1;
            get_regs_snap();
            return;
        }
        if (cant_elems == BUFFER_SIZE){
            return;
        }
        if(last == BUFFER_SIZE) last = 0; // Reposition of both the first and last pointer
        if(first == BUFFER_SIZE) first  = 0;
        buff[last++] = keyboard_matrix[key];
        cant_elems++;
    }
}

int get_control(){
    return control;
}
#include <libc.h>
#include <stdint.h>
#include <stdarg.h>

static unsigned int log(uint64_t n, int base) {
    unsigned int count = 1;
    while (n /= base)
        count++;
    return count;
}

static int isnumber(int n){
    return ((n) >= '0' && (n) <= '9');
}

void scanf(char* readbuf, uint64_t maxLen){

}

// https://www.equestionanswers.com/c/c-printf-scanf-working-principle.php
// usamos esta biblioteca para el manejo de argumentos variables

void printf(char * fmt, ...){
    va_list vl;  //donde se guardan los argumentos variables
    va_start(vl, fmt);
    va_printf(fmt, vl);
    va_end(vl);
}

void va_printf(char* fmt, va_list args){
    char buffer[] = {0};
    char * aux = fmt;           //puntero
    while(*aux){
        if(*aux == '%'){
            aux++;
            int dx = strtoi(aux, &aux);   //si es numero lo devuelve en formato decimal sino develve 0
            int len;

            switch (*aux)
            {
            case 'c':       //es un char
                putchar(va_arg(args, int));
                break;
            
            case 'd':    //es un entero
                len = itoa(va_arg(args, uint64_t), buffer, 10);     //esta en base 10
                printchars('0', dx-len);
                puts(buffer);
                break;
            
            case 'x':       //hexadcimal
                len = itoa(va_arg(args, uint64_t), buffer, 10);     //esta en base 16
                printchars('0', dx-len);
                puts(buffer);
                break;

            case 's':       //es un string
                printchars(' ', dx);
                puts(va_arg(args, char *));
                break;
            }
        }else {
            putchar(*aux);
        }
        aux++;
    }
}

void putchar(char c){
    write(1, c);
}

void puts(const char* s){
    while (*s)
    {
        putchar(*s++);
    } 
}

void printchars(char c, int n){
    while (n>0)
    {
        putchar(c);
        n--;
    }    
}

int itoa(uint64_t n, char* buffer, int base){
    if(n==0){
        buffer[0] = '0';
        buffer[1] = '\0';
        return 1;
    }

    unsigned int len=0;
    int i = 0;
    if( n<0 && base==10){
        n = -n;
        buffer[i] = '-';
        len++;
        i++;
    }
    
    len += log(n, base);
    while( n!=0){
        int res = n%base;
        if(res > 9){
            buffer[len-i-1]= (res-10) + 'A';
        } else{
            buffer[len-i-1] = res + '0';
        }
        n /= base;
        i++;
    }
    buffer[i] = '\0';
    return len;

}

int strtoi(char* s, char ** end){
    int n=0;
    while (isnumber(*s)){
        n = n * 10 + (*s++) - '0';
    }
    *end = s;
    return n;
}
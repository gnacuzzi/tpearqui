#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>


void printf(const char * fmt, ...);

int strcmp(const char * s1, const char * s2);

void putchar(char c);

void puts(const char * s);

void printchars(char c, int n);

int strtoi(char* s, char ** end);

int itoa(uint64_t n, char* buffer, int base);

void clear();

char readchar();


#endif
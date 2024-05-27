#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>
#include <stdbool.h>


void printf(const char * fmt, ...);

int strcmp(const char * s1, const char * s2);

void putchar(char c);

void puts(const char * s);

void printchars(char c, int n);

int strtoi(char* s, char ** end);

int itoa(int n, char* buffer, int base);

void clearscreen();

char readchar();

bool isNumber(char ch);

char scanInput();

int ctoi(char  s);

int scanf(char* buffer);

#endif
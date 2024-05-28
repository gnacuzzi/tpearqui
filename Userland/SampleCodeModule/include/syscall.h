#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>


void write(int fd, char c);

uint8_t read_char(int fd);

void clear_screen();

void get_seconds(int * sec);
void get_minutes(int * min);
void get_hours(int * hours);


setlettersize(int size);	

uint64_t * getRegs(uint64_t * regarr);

int get_control();

void make_sound(uint64_t freq, uint64_t time);

#endif
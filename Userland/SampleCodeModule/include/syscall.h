#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>


void write(int fd, char c);

uint8_t read_char(int fd);

void clear_screen();

uint8_t get_seconds();

setlettersize(int size);	

uint64_t * getRegs(uint64_t * regarr);

#endif
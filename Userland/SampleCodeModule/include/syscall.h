#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>


void write(int fd, char c);

uint8_t read(char * buffer, uint64_t len);

void clear_screen();

#endif
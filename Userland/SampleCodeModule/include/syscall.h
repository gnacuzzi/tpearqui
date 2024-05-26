#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>


void write(int fd, char c);

uint8_t read_char(int fd);

void clear_screen();

uint32_t get_seconds();

#endif
#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>


void write(int fd, char c);


uint8_t read(int fd);

#endif
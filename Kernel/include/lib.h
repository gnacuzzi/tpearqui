#ifndef LIB_H
#define LIB_H

#include <stdint.h>
#define REGS 17 
void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
uint64_t * get_snapshot();
void print_regs(uint64_t rip, uint64_t rsp, uint64_t * stack);
void copy_registers(uint64_t * stack);

char *cpuVendor(char *result);
char getKey();
int get_sec(); 
int get_min();
int get_hour();
void save_registers();
void beep(uint64_t freq);
void stop_beep();

#endif
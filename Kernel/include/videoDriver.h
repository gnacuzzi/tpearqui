#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H 

#include <stdint.h>
#define BLACK 0x000000
#define WHITE 0xFFFFFF

typedef struct {
	uint8_t b;
	uint8_t g;
	uint8_t r;
} Color;

void putPixel(Color color, uint64_t x, uint64_t y);
void draw_char(char c);
void draw_string(const char* str);
void draw_rect(int x, int y, int width, int height, Color color);
void clear_screen();
static void* getPtrToPixel(uint16_t x, uint16_t y);
void print_new_line(void);
void set_lettersize(int size);

#endif

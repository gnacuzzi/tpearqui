#include <stdint.h>
#define BLACK 0x000000
#define WHITE 0xFFFFFF

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void draw_char(char c);
void draw_string(const char* str);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void clear_screen();
int getPosition(int x, int y);



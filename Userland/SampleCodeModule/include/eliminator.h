#ifndef ELIMINATOR_H
#define ELIMINATOR_H

void start_eliminator();

void starting_screen();

void settings();

void play();

typedef struct {
	uint8_t b;
	uint8_t g;
	uint8_t r;
} Color;

typedef union {
	Color color;
	uint32_t bits;
} ColorInt;

#define SILVER ((Color){173, 169, 170})

#endif
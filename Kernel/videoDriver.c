#include <videoDriver.h>
#include <stdint.h>
#include <font.h>
#include <videoDriver.h>
#include <lib.h>

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

#define WIDTH VBE_mode_info->width
#define HEIGHT VBE_mode_info->height
uint16_t cursor_x = 0;
uint16_t cursor_y = 0;

Color penColor = {255, 255, 255};
Color backColor = {0, 0, 0};

static void* getPtrToPixel(uint16_t x, uint16_t y) {
    return (void*)(VBE_mode_info->framebuffer + 3 * (x + (y * (uint64_t)VBE_mode_info->width)));
}

void putPixel(Color color, uint64_t x, uint64_t y) {
	if (x >= VBE_mode_info->width || y >= VBE_mode_info->height)
        return;

    Color* pos = (Color*)getPtrToPixel(x, y);
    *pos = color;
}

void draw_rect(int x, int y, int width, int height, Color color){
	if (x >= VBE_mode_info->width || y >= VBE_mode_info->height)
        return;
    
    uint16_t maxWidth = VBE_mode_info->width - x;
    if (width > maxWidth) width = maxWidth;
    
    uint16_t maxHeight = VBE_mode_info->height - y;
    if (height > maxHeight) height = maxHeight;

    Color* ptr = (Color*)getPtrToPixel(x, y);
    unsigned int adv = VBE_mode_info->width - width;
    for (int i=0; i<height; i++) {
        for (int c=0; c<width; c++)
            *(ptr++) = color;
        ptr += adv;
    }
}

void clear_screen(){
	uint8_t* pos = (uint8_t*)((uint64_t)VBE_mode_info->framebuffer);
    for (uint32_t len = 3 * (uint32_t)VBE_mode_info->width * VBE_mode_info->height; len; len--, pos++)
        *pos = 0;
	cursor_x = 0;
	cursor_y = 0;
}

void print_new_line(void){
	cursor_x = 0; // pen x is set to full left.

    // If there is space for another line, we simply advance the pen y. Otherwise, we move up the entire screen and clear the lower part.
    if (cursor_y + (2 * CHAR_HEIGHT) <= VBE_mode_info->height) {
        cursor_y += CHAR_HEIGHT;
    } else {
        void* dst = (void*)((uint64_t)VBE_mode_info->framebuffer);
        void* src = (void*)(dst + 3 * (CHAR_HEIGHT * (uint64_t)VBE_mode_info->width));
        uint64_t len = 3 * ((uint64_t)VBE_mode_info->width * (VBE_mode_info->height - CHAR_HEIGHT));
        memcpy(dst, src, len);
        memset(dst + len, 0, 3 * (uint64_t)VBE_mode_info->width * CHAR_HEIGHT);
    }
}

//chequear y hay que agregar que se pueda agrandar la letr
//poner algo tipo default color pero por ahora dejo el WHITE
void draw_char(char c) {
    if (c == '\n') {
        print_new_line();
        return;
    }
/*
    if (c == '\b') { // Manejar backspace
        // Limitar el borrado solo a la línea actual
        if (cursor_x > 2*CHAR_WIDTH) {
            cursor_x -= CHAR_WIDTH;

            // Borrar el carácter en la posición actual del cursor
            for (int h = 0; h < CHAR_HEIGHT; h++) {
                Color* pos = (Color*)getPtrToPixel(cursor_x, cursor_y + h);
                for (int w = 0; w < CHAR_WIDTH; w++) {
                    pos[w] = backColor; // Usar bgColor para borrar
                }
            }
        }
        return;
    }
*/
    if (c >= FIRST_CHAR && c <= LAST_CHAR) {
        const char* data = font + 32 * (c - 33);
        for (int h = 0; h < 16; h++) {
            Color* pos = (Color*)getPtrToPixel(cursor_x, cursor_y + h);
            if (*data & 0b00000001) pos[0] = penColor;
            if (*data & 0b00000010) pos[1] = penColor;
            if (*data & 0b00000100) pos[2] = penColor;
            if (*data & 0b00001000) pos[3] = penColor;
            if (*data & 0b00010000) pos[4] = penColor;
            if (*data & 0b00100000) pos[5] = penColor;
            if (*data & 0b01000000) pos[6] = penColor;
            if (*data & 0b10000000) pos[7] = penColor;
            data++;
            if (*data & 0b00000001) pos[8] = penColor;
            data++;
        }
    }

    cursor_x += CHAR_WIDTH;
    if (cursor_x > VBE_mode_info->width - CHAR_WIDTH) {
        print_new_line();
    }
}


void draw_string(const char* str) {
    while (*str) {
        draw_char(*str); 
        str++;
    }
}

//falta lo de los colores de las fuentes
//falta lo del tamaño de las fuentes

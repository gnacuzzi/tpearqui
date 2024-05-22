//#include <videoDriver.h>
#include <stdint.h>
#include <font.h>
#include <videoDriver.h>

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

int getPosition(int x, int y){
	return (x * VBE_mode_info->bpp/8) + (y * VBE_mode_info->pitch);
}

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

void draw_rect(int x, int y, int width, int height, uint32_t color){
	if (x > WIDTH || y > HEIGHT) return;
	if (width + x > WIDTH) width = WIDTH - x;
	if (height + y > HEIGHT) height = HEIGHT - y;
	
	uint8_t * framebuffer = (uint8_t *) ((u_int64_t)VBE_mode_info->framebuffer + getPosition(x, y));
	//quizas para esto puedo hacer funciones de los colores
	int blue = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int red = (color >> 16) & 0xFF;

	for (int i = x; i < x + width; i++){
		for (int j = y; j < y + height; j++){
			framebuffer = (uint8_t *) ((u_int64_t)VBE_mode_info->framebuffer + getPosition(i, j));
			framebuffer[getPosition(i, j)] = blue;
			framebuffer[getPosition(i, j) + 1] = green;
			framebuffer[getPosition(i, j) + 2] = red;
		}
	}
}

void clear_screen(){
	draw_rect(0, 0, WIDTH, HEIGHT, BLACK);
}

//chequear y hay que agregar que se pueda agrandar la letra
void draw_char(int x, int y, char c, uint8_t color) {
    if (c < FIRST_CHAR || c > LAST_CHAR) {
        return; // Carácter no válido
    }

    int index = (c - FIRST_CHAR) * 16;
    for (int i = 0; i < 16; i++) {
        uint8_t line = font[index + i];
        for (int j = 0; j < 8; j++) {
            if (line & (0x80 >> j)) {
                putPixel(color, x + j, y + i);
            }
        }
    }
}


void draw_string(int x, int y, const char* str, uint8_t color) {
    while (*str) {
        draw_char(x, y, *str, color);
        x += 8; 
        str++;
    }
}

//falta lo de los colores de las fuentes
//falta lo del tamaño de las fuentes

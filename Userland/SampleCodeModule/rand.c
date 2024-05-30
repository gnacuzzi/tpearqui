#include "include/rand.h"

// Definimos las constantes del LCG
#define A 1664525
#define C 1013904223
#define M 4294967296 // 2^32
unsigned long seed = 1; // Semilla inicial

void srand(unsigned long s);

// Función para establecer la semilla
void srand(unsigned long s) {
    seed = s;
}

char rand_char() {
    seed = (A * seed + C) % M;
    // Mapeamos el resultado a 'w', 'a', 's' o 'd'
    switch (seed % 4) {
        case 0: return 'W';
        case 1: return 'A';
        case 2: return 'S';
        case 3: return 'D';
        default: return 'W'; // Caso por defecto, aunque no debería llegar aquí
    }
}
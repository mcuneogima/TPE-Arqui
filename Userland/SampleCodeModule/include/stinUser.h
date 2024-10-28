#include <stdint.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

char getchar();

void putchar(char carac);

void printHexa(uint64_t value);

void print(char * string);

void printColor(char * string, int color, int bg);

void putCharColor(char carac, int color, int bg);

void printBase(uint64_t value, uint32_t base);

void zoomIn();

void zoomOut();

void imprimirRegistros();

void printRegistros(uint64_t* registros);

void sleepUser(int segs);
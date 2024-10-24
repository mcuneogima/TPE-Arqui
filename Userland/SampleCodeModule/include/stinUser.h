#include <stdint.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

char getchar();

void putchar(char carac);

void printHexa();

void print(char * string);

void printColor(char * string, int color, int bg);

void putCharColor(char carac, int color, int bg);

void printBase(uint64_t value, uint32_t base);
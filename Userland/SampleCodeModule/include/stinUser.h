#include <stdint.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

extern void write(int fd, char * str, int leng, int color, int bg);

extern void read(int fd, char * buffer, int count);

extern void sleep(int seg);

char getchar();

void printNL();

void printTAB();

void putchar(char carac);

void printHexa();
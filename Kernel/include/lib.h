#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char getSeconds();
char getMinutes();
char getHours();
char getDoW();
char getMonth();
char getYear();
char returnKBOutputInterrupt();
char *cpuVendor(char *result);
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);

#endif
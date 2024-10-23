#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);

void drawChar(uint8_t * characterBitmap, uint64_t x, uint64_t y, uint32_t fontColor, uint32_t backgroundColor);

void printf(const char *string, uint64_t x_char, uint64_t y_char, uint32_t fontColor, uint32_t backgroundColor);

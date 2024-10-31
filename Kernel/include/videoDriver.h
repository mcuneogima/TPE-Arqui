#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);

void drawChar(uint64_t *characterBitmap, uint64_t x, uint64_t y, uint32_t fontColor, uint32_t backgroundColor);

void printVideo(const char *string, uint32_t fontColor, uint32_t backgroundColor);

void putcharVideo(char character, uint32_t font, uint32_t background);

void zoomIn();

void zoomOut();

void drawPixel(int color, int x, int y);

void setCursor(int x, int y);

void getScreenDetails(int * width, int * height);

int isValidCoordinates(int x, int y);

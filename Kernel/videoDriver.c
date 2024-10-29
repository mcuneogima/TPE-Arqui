#include <videoDriver.h>
#include <stdint.h>
#include <string.h>
#include <font.h>
#include <clock.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define TAB_SEPARATION 4

#define LINES_SMALL SCREEN_HEIGHT/16
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


int scale=1;
int	x_char = 8;
int	y_char = 16;
int x_offset=0;
int y_offset=0;
	
int last_xoffset_per_line[LINES_SMALL]={0};

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

void drawChar(uint64_t *characterBitmap, uint64_t x, uint64_t y, uint32_t fontColor, uint32_t backgroundColor) {
    int fontHeight = y_char;
	int fontWidth = x_char;

	// Recorre cada fila del caracter
    for (int row = 0; row < fontHeight; row++) {
        uint64_t bits = characterBitmap[row];  // Tomamos una fila del mapa de bits

        // Recorremos cada columna de la fila usando una mascara que abarque todo el ancho de la font
        for (uint8_t col = 0; col < fontWidth; col++) {
            // Usamos una mascara para analizar cada bit, empezando por el mas significativo
            uint64_t mask = (uint64_t)1 << (fontWidth - 1 - col);

            // Dibujamos el pixel en funcion de si el bit esta encendido o apagado
            putPixel((bits & mask) ? fontColor : backgroundColor, x + col, y + row);
        }
    }
}

void zoomIn(){
	if(scale<4){
		scale++;
		x_char=scale*getFontWidth();
		y_char=scale*getFontHeight();
	}
}
void zoomOut(){
	if(scale>1){
		scale--;
		x_char=scale*getFontWidth();
		y_char=scale*getFontHeight();
	}
}

void changeFontScale(uint8_t * originalBitmap, uint64_t * newBitmap) {
	// Definimos los tamaños de las nuevas y viejas font
    uint8_t originalFontHeight = getFontHeight();
    uint8_t originalFontWidth = getFontWidth();
    uint8_t newFontHeight = y_char;
    uint8_t newFontWidth = x_char; 

    // Limpiamos el nuevo bitmap para que no haya datos previos
    memset(newBitmap, 0, newFontHeight * sizeof(uint64_t));

    // Recorremos los pixeles del bitmap original
    for (uint8_t i = 0; i < originalFontHeight; i++) {
        for (uint8_t j = 0; j < originalFontWidth; j++) {
            // Verificamos si el bit en (i, j) está encendido en el bitmap original
            if (originalBitmap[i] & (1 << (originalFontWidth - 1 - j))) {
                // Mapeamos el bit encendido a la escala deseada
                for (uint8_t y = 0; y < scale; y++) {
                    for (uint8_t x = 0; x < scale; x++) {
                        // Calculamos la posicion en el nuevo mapa de bits
                        uint8_t newRow = i * scale + y;
                        uint8_t newCol = j * scale + x;
                        // Encendemos los bits correspondientes en la nueva matriz
                        newBitmap[newRow] |= (1 << (newFontWidth - 1 - newCol));
                    }
                }
            }
        }
    }
}



void putcharVideo(char character, uint32_t fontColor, uint32_t backgroundColor){
	// Matriz para la nueva escala
    uint64_t scaleBitmap[y_char];

	if(character=='\t'){
		char leave=0;
		for(int i=0; i<TAB_SEPARATION && !leave; i++){
			if(x_offset+x_char>SCREEN_WIDTH){
				leave=1;
				if(y_offset+2*y_char<=SCREEN_HEIGHT){
					y_offset+=y_char;
					x_offset=0;
				}

			}
			else{
				changeFontScale(getFontChar(' '), scaleBitmap);
				drawChar(scaleBitmap, x_offset, y_offset, fontColor, backgroundColor);
				x_offset+=x_char;
				last_xoffset_per_line[y_offset/16]=x_offset;
			}
		}

	}
	else if(character == '\n'){
		if(y_offset+2*y_char<=SCREEN_HEIGHT){
			last_xoffset_per_line[y_offset/16]=x_offset;
			x_offset=0;
			y_offset+=y_char;
		}

	}
	else if(character == 8){ //ascii backspace
		changeFontScale(getFontChar(' '), scaleBitmap);
		if(x_offset==0){ // si estoy en principio de linea y no estoy al principio de pantalla retorno a ultima posicion impresa en la linea anterior
			if(y_offset==0){ 
				return;
			}
			y_offset-=y_char;
			x_offset=(last_xoffset_per_line[y_offset/16]==0)?0:last_xoffset_per_line[y_offset/16]-x_char;
			drawChar(scaleBitmap, x_offset, y_offset, fontColor, 0);
		}
		else{
			x_offset-=x_char;
			drawChar(scaleBitmap, x_offset, y_offset, fontColor, 0);
			last_xoffset_per_line[y_offset/16]=x_offset;
		}
	}
	else{
		changeFontScale(getFontChar(character), scaleBitmap);
    	if(x_offset+x_char<=SCREEN_WIDTH){
			drawChar(scaleBitmap, x_offset, y_offset, fontColor, backgroundColor);
			x_offset += x_char;  // Avanzamos el cursor el ancho del pixel (8 píxeles) para el siguiente carácter
			last_xoffset_per_line[y_offset/16]=x_offset;
		}
		else{
			if(y_offset+2*y_char<=SCREEN_HEIGHT){
				x_offset=0;
				y_offset+=y_char;
				drawChar(scaleBitmap, x_offset, y_offset, fontColor, backgroundColor);
				x_offset+=x_char;
				last_xoffset_per_line[y_offset/16]=x_offset;
			}

		}

	}

}

void printVideo(const char *string, uint32_t fontColor, uint32_t backgroundColor) {
	// Imprimimos el caracter correspondiente hasta llegar al final del string (Null Terminated)
    while (*string != 0) {
        putcharVideo(*string, fontColor, backgroundColor);
        string++;
    }
}

void getScreenDetails(int * width, int * height){
	*width=SCREEN_WIDTH;
	*height=SCREEN_HEIGHT;
}

void setCursor(int x, int y){
	if(isValidCoordinates(x,y)){
		x_offset=x;
		y_offset=y;
	}
}
void drawPixel(int color, int x, int y){
	if(isValidCoordinates(x,y)){
		putPixel(color,x,y);
	}
}

int isValidCoordinates(int x, int y){
	return x>=0 && x<=SCREEN_WIDTH && y>=0 && y<=SCREEN_HEIGHT;
}

void clockTime(){
	// printDay();
	printHour();
}

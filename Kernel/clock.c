#include <clock.h>

#define TIME_ZONE -3

// buffer auxiliar
static char buffer[64] = {0};

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2){
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

static void printBase(uint64_t value, uint32_t base){
    // si es solo un digito, le agrego un 0 adelante
    if(uintToBase(value, buffer, base) == 1){
        buffer[2]=0; // Null Terminated
        buffer[1]=buffer[0];
        buffer[0]='0';
    }
    printVideo(buffer, getColor(WHITE), getColor(BLACK));
}

// Decodifica el valor binario a decimal
static uint64_t decode(uint64_t time) {
    return (time >> 4) * 10 + (time & 0x0F);
}

// Función hecha en asm dentro de Kernel\asm\libasm.asm
uint64_t getSeconds();
uint64_t getMinutes();
uint64_t getHours();

void printHour(){
    printVideo("\n\n\tHour: ", getColor(WHITE), getColor(BLACK));
	int hours = decode(getHours())+TIME_ZONE;
	hours += (hours<0||hours>23)?24:0;
    printBase((uint64_t)hours, 10);
    printVideo(":", getColor(WHITE), getColor(BLACK));
    printBase(decode(getMinutes()), 10);
    printVideo(":", getColor(WHITE), getColor(BLACK));
    printBase(decode(getSeconds()), 10);
}



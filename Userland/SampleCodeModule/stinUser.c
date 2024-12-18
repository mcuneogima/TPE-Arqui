#include "include/stinUser.h"
#include "include/libasmUser.h"
#include "include/stinUser.h"

static char buffer[64] = { '0' };

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

void print(char * string){
    printColor(string,0x00ffffff,0);
}

void printColor(char * string, int color, int bg){
	int i;
    for(i=0;string[i]!='\0';i++){
    	putCharColor(string[i],color,bg);
    }
}

char getchar(){
    char caracter;
    read(0,&caracter,1);
	return caracter;
}

void putchar(char carac){
    putCharColor(carac,0x00ffffff,0);
}

void putCharColor(char carac, int color, int bg){
    write(1, &carac,1,color,bg);
}
//ver lo de backspace

void printHexa(uint64_t value){
	printBase(value, 16);
}

void printBase(uint64_t value, uint32_t base){
    uintToBase(value, buffer, base);
    print(buffer);
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

void zoomIn(){
	zoom(1);
}
void zoomOut(){
	zoom(-1);
}

void imprimirRegistros(){
    impRegs();
}

void sleepUser(int segs){
    sleep(segs);
}

uint64_t getMS(){
    uint64_t milis;
    getMiliSecs(&milis);
    return milis;
}

void clock(){
    char * str="00:00:00";
    getClock(str);
    printClock(str);
}

void printClock(char * str) {
    print("\n\n\tHour: ");
    print(str);
    print("\n");
}

char getcharNonLoop(){
    char charac;
    getcharNL(&charac);
    return charac;
}


unsigned int generarNumeroAleatorio(uint64_t *seed) {
    // Parámetros del generador congruencial lineal
    const unsigned long a = 1664525; // Multiplicador
    const unsigned long c = 1013904223; // Incremento
    const unsigned long m = 4294967296; // 2^32

    // Generar el siguiente número aleatorio
    *seed = (*seed * a + c) % m;
    return *seed;
}

void sound(int index){
    playSound(index);
}

int numeroAleatorioEntre(int min, int max, uint64_t *seed) {
    unsigned int numero = generarNumeroAleatorio(seed);
    return (numero % (max - min + 1)) + min;
}

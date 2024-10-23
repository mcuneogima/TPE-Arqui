#include "include/stinUser.h"
#include "include/libasmUser.h"
#include "include/stinUser.h"
/*
static char buffer[64] = { '0' };

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

extern void write(int fd, char * str, int leng, int color, int bg);

extern void read(int fd, char * buffer, int count);

extern void sleep(int seg);

char getchar();

void printNL();

void printTAB();

void putchar(char carac);

void printHexa();

void print(char * string){
    printColor(string,0x00ffffff,0);
}

void printColor(char * string, int color, int bg){
    for(int i=0;string[i]!='\0';i++){
        if(string[i]=='\n'){
            printNL();
        }else if(string[i]=='\t'){
            printTab();
        }else{
            putCharColor(string[i],color,bg);
        }
    }
}

char getChar(){
    char caracter;
    read(0,&caracter,1);
}

void putchar(char carac){
    putCharColor(carac,0x00ffffff,0);
}

void putCharColor(char carac, int color, int bg){
    write(1, &carac,1,color,bg);
}
//ver lo de backspace

void printNL(){

}
void printTAB(){
    for(int i=0;i<4;i++){
        putChar(" ");
    }
}

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

*/
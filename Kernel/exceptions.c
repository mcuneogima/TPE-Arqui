#include <stdint.h>
#include <interrupts.h>
#include <time.h>
#include <moduleLoader.h>
#include <videoDriver.h>
#include <exceptions.h>


#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6

static void zero_division();

void invalidOpcode();

typedef int (*EntryPoint)();

static void * const sampleCodeModuleAddress = (void*)0x400000;



void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	else if(exception==INVALID_OPCODE_ID)
		invalidOpcode();
}

static void zero_division() {
	// Handler para manejar excepcíon
	printVideo("\nDividiste por 0\nRetornando a terminal\n", 0xffffff, 0);
	sleep(3*18);
}

void invalidOpcode(){
	printVideo("\nOpcode invalido\nRetornando a terminal\n", 0xffffff, 0);
	sleep(3*18);
}

void printRegistros(uint64_t* registros){
    printVideo("\n\nRAX: ", 0xffffff, 0);
    PrintBase(registros[0],16);
    printVideo("\n", 0xffffff, 0);

    printVideo("RBX: ", 0xffffff, 0);
    PrintBase(registros[1],16);
    printVideo("\n", 0xffffff, 0);

    printVideo("RCX: ", 0xffffff, 0);
    PrintBase(registros[2],16);
    printVideo("\n", 0xffffff, 0);

    printVideo("RDX: ", 0xffffff, 0);
    PrintBase(registros[3],16);
    printVideo("\n", 0xffffff, 0);

    printVideo("RSI: ", 0xffffff, 0);
    PrintBase(registros[4],16);
    printVideo("\n", 0xffffff, 0);

    printVideo("RDI: ", 0xffffff, 0);
    PrintBase(registros[5],16);
    printVideo("\n", 0xffffff, 0);

    printVideo("RBP: ", 0xffffff, 0);
    PrintBase(registros[6],16);
    printVideo("\n", 0xffffff, 0);

    printVideo("RSP: ", 0xffffff, 0);
    PrintBase(registros[7],16);
    printVideo("\n", 0xffffff, 0);
	
	printVideo("R8: ", 0xffffff, 0);
    PrintBase(registros[8],16);
    printVideo("\n", 0xffffff, 0);

    printVideo("R9: ", 0xffffff, 0);
    PrintBase(registros[9],16);
    printVideo("\n", 0xffffff, 0);

	printVideo("RIP: ", 0xffffff, 0);
    PrintBase(registros[10],16);
    printVideo("\n", 0xffffff, 0);

	printVideo("CS: ", 0xffffff, 0);
    PrintBase(registros[11],16);
    printVideo("\n", 0xffffff, 0);

	printVideo("RFLAGS: ", 0xffffff, 0);
    PrintBase(registros[12],16);
    printVideo("\n", 0xffffff, 0);
}


static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
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

void PrintBase(uint64_t value, uint32_t base)
{
	int buffer[100];
    uintToBase(value, buffer, base);
    printVideo(buffer, 0xffffff, 0);
}
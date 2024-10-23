#include <time.h>
#include <interrupts.h>
#include <naiveConsole.h>

static unsigned long ticks = 0;
int last_seconds = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

//funcion sleep en seg 
//termina siendo la syscall sleep
void sleep(int seconds){
	int current_seconds=ticks/18;
	while(current_seconds+seconds!=ticks/18){
		_hlt();
	}
}
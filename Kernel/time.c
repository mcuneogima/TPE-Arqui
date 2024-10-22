#include <time.h>
#include <naiveConsole.h>

static unsigned long ticks = 0;
int called_int = 0;
char* msg = "5 seconds passed";
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

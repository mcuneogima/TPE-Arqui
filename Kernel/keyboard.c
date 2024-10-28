#include <keyboard.h>
#include <videoDriver.h>

#define BACKSPACE_P 0x0E
#define ENTER_P 0x1C
#define LSHIFT_P 0x2a
#define CAPSLOCK_P 0x3a
#define RSHIFT_P 0x36
#define LCTRL_P 0x1d
#define RCTRL_P 0xe0
#define ESC_P 0x01
#define LALT_P 0x38
#define RALT_P 0x38

#define BACKSPACE_R 0x8E
#define ENTER_R 0x9C
#define LSHIFT_R 0xaa
#define CAPSLOCK_R 0xba


#define BUFFER_LENGTH 15

char buffer[BUFFER_LENGTH];
int dim=0;
int toPrint=0;
int upperCase=0;
int shift=0;
    
void bufferLoader(char input){
    char release = input;
    release = release >> 7;
    char key = input & 0x7F;
    if(key==LSHIFT_P||key==RSHIFT_P){
        shift=!release;
        return;
    }
    if(input==CAPSLOCK_P){ //veo si seria mayus
        upperCase=1-upperCase;
    }
    char checker=input;
    if(!(release)&&!isSpecialKey(input)){  //guardo teclas apretadas no soltadas
        buffer[dim++]=input;
        dim%=BUFFER_LENGTH;
    }

}

char getKey(){
    if (toPrint == dim)
		return -1;
	unsigned char toRet = buffer[toPrint++];
//	buffer[toPrint++] = 0;
	toPrint %= BUFFER_LENGTH;
	return toRet;
}

int isUpperCase(){
    return (upperCase)?!shift:shift;
}

int isSpecialKey(char scancode) {
    return 
    (scancode == LSHIFT_P)    || (scancode == RSHIFT_P)     || 
    (scancode == LCTRL_P)     || (scancode == RCTRL_P)      || 
    (scancode == LALT_P)      || (scancode == RALT_P)       ||
    (scancode == CAPSLOCK_P)  || (scancode == ESC_P)        ||
    (scancode == 0x57)      || (scancode == 0x58)       ||
    (scancode >= 0x3B);
}
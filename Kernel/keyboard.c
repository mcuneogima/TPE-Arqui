#include <keyboard.h>

#define BACKSPACE_P 0x0E
#define ENTER_P 0x1C
#define LSHIFT_P 0x2a
#define CAPSLOCK_P 0x3a

#define BACKSPACE_R 0x8E
#define ENTER_R 0x9C
#define LSHIFT_R 0xaa
#define CAPSLOCK_R 0xba


#define BUFFER_LENGTH 15

char buffer[BUFFER_LENGTH];
int dim=0;
int toPrint=0;
int upperCase=0;
    
void bufferLoader(char input){
    if(input==LSHIFT_P||input==LSHIFT_R||input==CAPSLOCK_P){ //veo si seria mayus
        upperCase=!upperCase;
    }
    char checker=input;
    if(!(checker >> 7)){  //guardo teclas apretadas no soltadas
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
    return upperCase;
}
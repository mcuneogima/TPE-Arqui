#include <syscallDispatcher.h>
//funcion para obtener el ultimo caracter del buffer de entrada
char getChar();

//funcion para mostrar en salida estandar un caracter
void putChar(char character);

//funcion para imprimir un string
void write(char * string, int len, int color, int background);

//funcion para tomar un string de hasta longitud len de entrada estandar
 void read(char * buffer,int len);

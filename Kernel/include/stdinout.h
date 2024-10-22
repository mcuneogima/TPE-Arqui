//funcion para obtener el ultimo caracter del buffer de entrada
char getChar();

//funcion para mostrar en salida estandar un caracter
void putChar(char character);

//funcion para imprimir un string
void write(FDS fd, char * string, int len);

//funcion para tomar un string de hasta longitud len de entrada estandar
 void read(FDS fd, char * buffer,int len);

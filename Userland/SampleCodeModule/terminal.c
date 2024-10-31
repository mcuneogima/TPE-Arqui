#include "include/stinUser.h"
#include "include/stringUser.h"
#include "include/terminal.h"
#include "include/screen.h"
#include "include/snake.h"
#include "include/exceptions.h"
#include <stdint.h>

#define STARTING_POSITION_X 0
#define STARTING_POSITION_Y 0

int charsPerLine[]={128,64,42};
int charSize=1;
int screenWidth;
int screenHeight;
int lastRunHeight=0;

void terminal(){
    char buffer[1000];
    char c;
    int i=0;
    int tabs=0;
    sound(1);
    getScreenSize(&screenWidth,&screenHeight);
    // while(1){
    //     putchar(getchar());
    // }
    refreshScreen();
    moveCursor(STARTING_POSITION_X,STARTING_POSITION_Y);
    putCharColor('>',0xFFCC0F,0);
    
    while(1){
        if((c=getchar())!='\n'){
            // if(c==0x48 || c==0xE0){        //pseudo codigo para la flechita
            //     print("paso");
            //     moveCursor(STARTING_POSITION_X, STARTING_POSITION_Y);
            //     clean(i+1);
            //     putCharColor('>',0xFFCC0F,0);
            //     print(bufferComands);
            //     i=previousLength;
            // }else 
            if(c==8){
                if(i>0){
                    i--;
                    putchar(c);
                }
                // moveCursor();
                // actualizarPantalla();
            }
            else if(c=='\t'){
                if(i+tabs*3+4<charsPerLine[charSize-1]*2){
                    tabs++;
                    buffer[i++]=c;
                    putchar(c);
                }
                
            }else{
                if((i+tabs*3+1)<charsPerLine[charSize-1]*2){
                    buffer[i++]=c;
                    putchar(c);
                }
                // actualizarPantalla();
            } 
        }
        else{
            buffer[i]=0;
            // strcpy(buffer, bufferComands);
            moveCursor(STARTING_POSITION_X, STARTING_POSITION_Y);
            clean(i+1+tabs*3); //limpio promt de comando 
            print("\n\n"); //bajo dos lineas
            clean(lastRunHeight*charsPerLine[charSize-1]); //limpio lo usado por el ultimo comando 
            moveCursor(STARTING_POSITION_X, STARTING_POSITION_Y);

            if(!strcmp(buffer,"help")){
                help();
                lastRunHeight=14;
            }
            else if(!strcmp(buffer,"zoom in")){
                if(charSize<3){
                    zoomIn();
                    charSize++;      
                }
                lastRunHeight=0;
            }
            else if(!strcmp(buffer,"zoom out")){
                 if(charSize>1){
                    zoomOut();
                    charSize--;      
                }
                lastRunHeight=0;
            }else if(!strcmp(buffer,"showRegisters")){
                imprimirRegistros();
                lastRunHeight=13;
            }else if(!strcmp(buffer,"exit")){
                print("Bye Bye");
                sound(2);
                sleepUser(20);
                refreshScreen();
                return;
            }else if (!strcmp(buffer,"snake")){
                while(charSize>1){
                    zoomOut();
                    charSize--;
                }
                snake();
                lastRunHeight=0;
                refreshScreen();
            }
            else if(!strcmp(buffer, "clock")){
                clock();
                lastRunHeight=1;
            }
            else if(!strcmp(buffer, "romper OpCode")){
                while(charSize>1){
                    zoomOut();
                    charSize--;
                }
                opcodeBreaker();
            }
            else if(!strcmp(buffer, "romper division")){
                while(charSize>1){
                    zoomOut();
                    charSize--;
                }
                divisionBreaker();
            }
            else{
                print("\n\nCommand ");
                print(buffer);
                print(" not found\n");
                lastRunHeight=2+1; //peor de los casos para la promt + linea cnf
            }

            moveCursor(STARTING_POSITION_X, STARTING_POSITION_Y);
            putCharColor('>',0xFFCC0F,0);
            // previousLength=i;
            tabs=0;
            i=0;
        }
    }

}

void clean(int ammount){
    for(int j=0;j<ammount;j++){
        putchar(' ');
    }
}


void help(){
    print("\n\nBienvenido a la terminal\n Comandos disponibles: \n \tzoom in para agrandar la letra. \n \tzoom out para achicar la letra.\n \tclock para ver la hora actual.\n \tshowRegisters para mostrar los registros en pantalla.\n \tsnake para jugar al juego de la viborita. \n \texit para cerrar la terminal.\n \tromper division para probar la excepcion de dividir por cero y volver a la terminal.\n \tromper OpCode para probar la excepcion de opcode y volver a la terminal. \n ");
}

void refreshScreen(){
    for(int i=0;i<=screenHeight;i++){
        for(int j=0;j<=screenWidth;j++){
            putPixel(0,j,i);
        }
    }
}

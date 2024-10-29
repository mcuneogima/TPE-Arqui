#include "include/snake.h"
#include "include/screen.h"
#include "include/stinUser.h"
#include "include/stringUser.h"

#define GRIS 0x808080
#define ROJO 0xFF0000
#define VERDECLARO 0x74FF33
#define VERDEOSCURO 0x266F04

#define NARANJA 0xFF8000
#define CIAN 0x0098D5
#define AMARILLO 0xFFCC0F



void snake(){
    int quit=0;
    char c;
    int i=0;
    char buffer[128];
    printColor("Bienvenido a snake!\n",ROJO,0x000000);
    print("Como jugar: El objetivo es agarrar las manzanas (rojo), para ello, el jugador 1 (naranja) se puede mover con 'wasd'\nY el jugador 2 (azul) con 'ijkl'.\nSeleccione numero de jugadores: ");
    printColor("[1jug]",NARANJA,0x000000);
    print("  o  ");
    printColor("[2jug]\n",CIAN,0x000000);
    printColor("[quit]  ",ROJO,0x000000);
    print("para salir, ");
    printColor("[play] ",AMARILLO,0x000000);
    print("para jugar\n");
    putCharColor('>',0xFFCC0F,0);
    printTablero(); //11x11 de cuadrados de 45x45
    while(!quit){
        c=getchar();
        if(c!='\n'){
            if(c==8){
                if(i>0){
                    i--;
                    putchar(c);
                }
            }else{
                if(i<128-1){
                    buffer[i++]=c;
                    putchar(c);
                }
            } 
        }
        else{
            buffer[i]=0;
            clearPromt(i);
            if(!strcmp(buffer,"1jug")){

            }
            else if(!strcmp(buffer,"2jug")){

            }
            else if(!strcmp(buffer,"quit")){
                quit=1;
            }else if(!strcmp(buffer,"play")){

            }
            i=0;
        }
    }
    PutManzana();
    // select player 
    //salir
    //juego
}


void clearPromt(int len){
    for(int i=0; i<len; i++){
        putchar(8);
    }
}

void printTablero(){
    printBordeHorizontal(3);
    for(int i=4;i<15;i++){ 
        printAS(5,i);     //filas del 1 al 14
        for(int j=6;j<17;j++){
            printCuadrado(j,i);
        }
        printAS(17,i);
    }
    printBordeHorizontal(15);
}

void printBordeHorizontal(int fila){
    for(int i=5;i<18;i++){
        printAS(i,fila);
    }
}

void printCuadrado(int col, int fila){
    int color;
    if(fila%2==0){
        if(col%2==0){
            color= VERDECLARO;
        }else{
            color= VERDEOSCURO;
        }
    }
    else{
        if(col%2==0){
            color=VERDEOSCURO;
        }else{
            color=VERDECLARO;
        }
    }
    for(int i=0;i<45;i++){
        for(int j=0;j<45;j++){
            putPixel(color,i+col*45,j+fila*45);
        }
    }
}


void printAS(int col, int fila){
    int color;
    for(int i=0;i<45;i++){
        for(int j=0;j<45;j++){
            color= ((j+i)%2==0)? GRIS: 0xFFFFFF;
            putPixel(color,i+col*45,j+fila*45);
        }
    }
}

void PutManzana(){
    int x=numeroAleatorioEntre(0,10, getMS());
    int y=numeroAleatorioEntre(0,10, getMS());

    for(int i=3;i<39;i++){
        for(int j=3;j<39;j++){
            putPixel(ROJO,i+x*45,y*45);
        }
    }
}


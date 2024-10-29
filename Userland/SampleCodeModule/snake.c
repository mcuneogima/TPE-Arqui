#include "include/snake.h"
#include "include/screen.h"
#include "include/stinUser.h"
#include "include/stringUser.h"

#define GRIS 0x808080
#define ROJO 0xFF0000
#define VERDECLARO 0x74FF33
#define VERDEOSCURO 0x266F04




void snake(){
    int quit=0;
    char c;
    int i=0;
    char buffer[128];
    print("Bienvenido a snake!\nComo jugar: El objetivo es agarrar las manzanas (rojo), para ello, el jugador 1 (azul) se puede mover con wasd y el jugador 2 \n(naranja) con ijkl.\nSeleccione numero de jugadores: [1jug], [2jug]\n[quit] para salir, [play] para jugar\n");
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
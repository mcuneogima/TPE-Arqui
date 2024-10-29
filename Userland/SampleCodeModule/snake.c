#include "include/snake.h"
#include "include/screen.h"

#define GRIS 0x808080
#define ROJO 0xFF0000
#define VERDECLARO 0x74FF33
#define VERDEOSCURO 0x266F04

void snake(){
    printTablero(); //16x16 de cuadrados de 64x64
    // select player 
    //salir
    //juego
}


void printTablero(){
    printBordeHorizontal(1);
    for(int i=2;i<10;i++){ 
        printAS(3,i);     //filas del 1 al 14
        for(int j=4;j<12;j++){
            printCuadrado(j,i);
        }
        printAS(12,i);
    }
    printBordeHorizontal(10);
}

void printBordeHorizontal(int fila){
    for(int i=3;i<13;i++){
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
    for(int i=0;i<64;i++){
        for(int j=0;j<64;j++){
            putPixel(color,i+col*64,j+fila*64);
        }
    }
}


void printAS(int col, int fila){
    int color;
    for(int i=0;i<64;i++){
        for(int j=0;j<64;j++){
            color= ((j+i)%2==0)? GRIS: 0xFFFFFF;
            putPixel(color,i+col*64,j+fila*64);
        }
    }
}
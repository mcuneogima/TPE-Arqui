#include "include/snake.h"
#include "include/screen.h"
#include "include/stinUser.h"
#include "include/stringUser.h"

#define GRIS 0x808080
#define ROJO 0xFF0000
#define VERDECLARO 0x74FF33
#define VERDEOSCURO 0x266F04
#define VIOLETA 0x9a4eae

#define TIME_INTERVAL 1

#define X 0
#define Y 1

#define STARTING_POS_X 2
#define STARTING_POS_Y 5

int played=0;
#define NARANJA 0xFF8000
#define CIAN 0x0098D5
#define AMARILLO 0xFFCC0F



void snake(){
    int quit=0;
    char c;
    int i=0;
    char buffer[128];
    int jugadores=1;
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
                jugadores=1;
            }
            else if(!strcmp(buffer,"2jug")){
                jugadores=2;
            }
            else if(!strcmp(buffer,"quit")){
                quit=1;
            }else if(!strcmp(buffer,"play")){
                if(jugadores==1){
                    sigleplayer();
                }else{
                    pvp();
                }
            }
            i=0;
        }
    }
    PutManzana();
    // select player 
    //salir
    //juego
}

void sigleplayer(){
    if(played==0){
        played=1;
    }
    else{
        printTablero();
    }
    int snk1[11*11][2];
    for(int i=0; i<3;i++){
        snk1[i][X]=STARTING_POS_X+i;
        snk1[i][Y]=STARTING_POS_Y;
        printCuadradoColor(STARTING_POS_X+i,STARTING_POS_Y, 0x00ff8000);
    }
    int len1=2;
    int crashed=0;
    int apple_x=8;
    int apple_y=5;
    printCuadradoColor(apple_x,apple_y,ROJO);
    int direc[][2]={{1,0},{-1,0},{0,1},{0,-1}};
    int dir=0;
    int cola=0;
    int siguiente;
    char pressed;
    int last_dir=0;
    uint64_t prev_ms=getMS();
    uint64_t ms=prev_ms;
    while(crashed==0){
        pressed=getcharNonLoop();
        if(pressed=='w'&&last_dir!=3){
            dir=3;
        }
        else if(pressed=='a'&&last_dir!=1){
                dir=1;
        }
        else if(pressed=='s'&&last_dir!=2){
                dir=2;
        }
        else if(pressed=='d'&&last_dir!=0){
                dir=0;
        }
        ms=getMS();
        if(ms>=prev_ms+TIME_INTERVAL){
            prev_ms=ms;
            if(!isValidPos1J(snk1[len1][X]+direc[dir][X],snk1[len1][Y]+direc[dir][Y],snk1, len1, cola)){
                crashed=1;
            }
            else{
                if(snk1[len1][X]+direc[dir][X]==apple_x&&snk1[len1][Y]+direc[dir][Y]==apple_y){
                    //getRandPos(&apple_x,&apple_y);
                    //printCuadradoColor(apple_x,apple_y,0x00ff0000);
                    siguiente=(len1+1)%(11+11);
                    snk1[siguiente][X]=snk1[len1][X]+direc[dir][X];
                    snk1[siguiente][Y]=snk1[len1][Y]+direc[dir][Y];
                    len1=siguiente;
                    printCuadradoColor(snk1[len1][X],snk1[len1][Y],0x00ff8000);
                }
                else{
                    siguiente=(len1+1)%(11+11);
                    snk1[siguiente][X]=snk1[len1][X]+direc[dir][X];
                    snk1[siguiente][Y]=snk1[len1][Y]+direc[dir][Y];
                    len1=siguiente;
                    printCuadradoColor(snk1[len1][X],snk1[len1][Y],0x00ff8000);
                    printCuadrado(snk1[cola][X],snk1[cola][Y]);
                    cola=(cola+1)%(11*11);
                }
            }
            last_dir=dir;
        }
    }
}

int isValidPos1J(int x,int y,int snake[][2], int len, int cola){
    if(x<0||y<0||x>10||y>10){
        return 0;
    }
    for(int i=cola; i!=len+1; i++){
        i%=(11*11);
        if(x==snake[i][X]&&y==snake[i][Y]){
            return 0;
        }
    }
    return 1;
}

void pvp(){

}

void printCuadradoColor(int x, int y, int color){
    x+=6;
    y+=4;
    for(int i=0; i<45; i++){
        for(int j=0; j<45; j++){
            putPixel(color,x*45+i,y*45+j);
        }
    }
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
            color= ((j+i)%2==0)? VIOLETA: GRIS;
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

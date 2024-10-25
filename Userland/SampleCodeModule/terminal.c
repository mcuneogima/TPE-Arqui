#include "include/stinUser.h"
#include "include/stringUser.h"
#include "include/terminal.h"
#include <stdint.h>

void terminal(){
    char buffer[1000];
    char c;
    int i=0;
    // while(1){
    //     putchar(getchar());
    // }
    putCharColor('>',0xFFCC0F,0);
    
    while(1){
        if((c=getchar())!='\n'){
            if(c==8){
                if(i>0){
                    i--;
                    putchar(c);
                }
                // moveCursor();
                // actualizarPantalla();
            }else{
                buffer[i++]=c;
                putchar(c);
                // actualizarPantalla();
            } 
        }
        else{
            buffer[i]=0;
            if(!strcmp(buffer,"help")){
                help();
            }
            else if(!strcmp(buffer,"zoom in")){
                zoomIn();
                refreshScreen();
            }
            else if(!strcmp(buffer,"zoom out")){
                zoomOut();
                refreshScreen();
            }
            moveCursor();
            clean(i+1);
            putCharColor('>',0xFFCC0F,0);
            i=0;
        }
    }

    // if(srcmp(buffer,"imprimirRegistros")){
    //     imprimirRegistros();
    // }
    // if(srcmp(buffer,"snake")){
    //     snake();
    // }
}

void clean(int ammount){
    for(int j=0;j<ammount;j++){
        putchar(8);
    }
}

void help(){
    print("\nBienvenido a la terminal\n Comandos disponibles: \n \tzoom in para agrandar la letra \n \tzoom out para achicar la letra\n");
}
void moveCursor(){

}

void refreshScreen(){

}

/*
void imprimirRegistros(){
    devolverRegistros();
}

void printRegistros(uint64_t* registros){
    print("RAX: ");
    printHexa(registros[0]);
    print("\n");

    print("RBX: ");
    printHexa(registros[1]);
    print("\n");

    print("RCX: ");
    printHexa(registros[2]);
    print("\n");

    print("RDX: ");
    printHexa(registros[3]);
    print("\n");

    print("RSI: ");
    printHexa(registros[4]);
    print("\n");

    print("RDI: ");
    printHexa(registros[5]);
    print("\n");

}
*/
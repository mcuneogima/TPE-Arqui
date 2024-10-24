#include "include/stinUser.h"
#include "include/stringUser.h"
#include <stdint.h>

void terminal(){
    char buffer[100];
    char c;
    int i=0;
    printColor("Terminal: ",0x008000,0);
    putchar(getchar());
    // while((c=getchar())!='\n'){
        
    //     if(c==8){
    //         i--;
    //         // moveCursor();
    //         // actualizarPantalla();
    //     }else{
    //         buffer[i++]=c;
    //         // actualizarPantalla();
    //     }
    // }
    // buffer[i]=0;
    // if(strcmp(buffer,"help")){
    //     help();
    // }
    // if(srcmp(buffer,"zoom in")){
    //     zoomIn();
    // }
    // if(srcmp(buffer,"zoom out")){
    //     zoomOut();
    // }
    // if(srcmp(buffer,"imprimirRegistros")){
    //     imprimirRegistros();
    // }
    // if(srcmp(buffer,"snake")){
    //     snake();
    // }
}

void help(){
    print("Bienvenido a la terminal\n Comandos disponibles: \n \tzoom in para agrandar la letra \n \tzoom out para achicar la letra\n");
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
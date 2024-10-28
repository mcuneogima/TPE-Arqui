#include "include/stringUser.h"

int strlen(char * string){
    int count=0;
    while(string[count]!=0){
        count++;
    }
    return count+1;
}

// int strcmp(char* s1, char* s2){
//     int flag=1, count=0;
//     for(int i=0;flag;i++){
//         if(s1[i]=='\0' && s2[i]=='\0'){
//             return 0;
//         }
//         count=s1[i]-s2[i];
//         flag=!count;
//     }
//     return count;
// }

int strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return *str1 - *str2; // Devuelve la diferencia de los caracteres
        }
        str1++;
        str2++;
    }
    return *str1 - *str2; // Si uno de los strings ha terminado
}

void strcpy(char* str1, char* str2){
    while(*str1!='\0'){
        *str2=*str1;
        str1++;
        str2++;
    }
    *str2=0;
}
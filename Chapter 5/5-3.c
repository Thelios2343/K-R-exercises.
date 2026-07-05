#include <stdio.h>

void str_cat(char *dest, char *src);

int main () {

    char dest[100] = "mundo ";
    char src [100] = "hola";

    str_cat(dest, src);
    
    printf("El string unido: %s\n", dest );
}

void str_cat(char *dest, char *src) {
    while(*dest != '\0') {
        dest++;
    }

    while(*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';
}

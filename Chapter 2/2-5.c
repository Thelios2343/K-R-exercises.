#include <stdio.h>

int any (char s1[], char s2[]); 
void limpiartexto(char text[]);

int any (char s1[], char s2[]) {
    int i, j;

    for (i = 0; s1[i] != '\0'; ++i) {
        for (j = 0; s2[i] != '\0'; ++j) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }
return -1;
}

void limpiartexto(char text[]) {
    int i = 0;

    while (text[i] != '\0') {
        if (text[i] == '\n') {
            text[i] = '\0';
            break;
        }
   }
}

int main () {
    char texto1[100];
    char texto2[10];

    printf("Ingresa una frase con un maximo de 100 caracteres: ");
    fgets(texto1, sizeof(texto1), stdin);

    printf("\nIngresa los caracteres para buscar coincidencias en la frase anterior (solo puedes un maximo de 10 caracteres: ");
    fgets(texto2, sizeof(texto2), stdin);

    int pos = any (texto1, texto2);

    printf("\ns1: \"%s\"\n", texto1);
    printf("s2: \"%s\"\n", texto2);

    if (pos != -1) {
        printf("Primera coincidencia en indice: %d ('%c')\n", pos, texto1[pos]);
    }
    else {
        printf("No hay ninguna coincidencia\n");
    }

}

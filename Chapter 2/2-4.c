#include <stdio.h>


void limpiartexto (char text[]); 
/* squeeze: elimina de s1 todos los caracteres que aparecen en s2 */
void squeeze(char s1[], char s2[]) {
    int i, j, k;
    int debe_eliminar;

    for (i = j = 0; s1[i] != '\0'; i++) {
        debe_eliminar = 0;
        
        /* verificar si el carácter actual está en s2 */
        for (k = 0; s2[k] != '\0'; k++) {
            if (s1[i] == s2[k]) {
                debe_eliminar = 1;
                break;
            }
        }
        
        /* si no debe eliminarse, lo conservamos */
        if (!debe_eliminar) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';  /* terminamos la cadena resultante */
}

void limpiartexto (char text[]) {
    
    int i = 0;

    while (text[i] != '\0') {
        if (text[i] == '\n') {
            text[i] = '\0';
            break;
        }
        ++i;
    }

}


int main() {

    printf ("Presione Ctrl + C para detener :D");
for (;;) {
    char texto1[100] ;
    char texto2[10] ;  
    
    printf("Ingresa una frase de maximo 100 caracteres: ");
    fgets(texto1, sizeof(texto1), stdin);
    limpiartexto(texto1);
    printf("Ingresa un maximo de 10 caracteres a eliminar de la frase: ");
    fgets(texto2, sizeof(texto2), stdin);
    limpiartexto(texto2);
    
    squeeze(texto1, texto2);
    
    printf("\nCadena resultante: \"%s\"\n", texto1);
    
    
        }
}

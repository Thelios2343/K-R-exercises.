#include <stdio.h>

int main(void) {
    int c, lastc = 0;
    int estado = 0;          /* 0=normal, 1=string, 2=char, 3=comment */
    int escape = 0;
    int paren = 0, bracket = 0, brace = 0;  
    int error = 0;
    
    while ((c = getchar()) != EOF) {
        
        if (estado == 3) {  
            if (lastc == '*' && c == '/') {
                estado = 0;
                lastc = 0;
            } else {
                lastc = c;
            }
            continue;
        }
        
    
        if ((estado == 1 || estado == 2) && escape) {
            escape = 0;
            lastc = c;
            continue;
        }
        
        if ((estado == 1 || estado == 2) && c == '\\') {
            escape = 1;
            lastc = c;
            continue;
        }
        
        /* Cambios de estado */
        if (estado == 0 && lastc == '/' && c == '*') {
            estado = 3;
            lastc = 0;
            continue;
        }
        
        if (estado == 0 && c == '"') {
            estado = 1;
        } else if (estado == 1 && c == '"') {
            estado = 0;
        } else if (estado == 0 && c == '\'') {
            estado = 2;
        } else if (estado == 2 && c == '\'') {
            estado = 0;
        }
        
        
        /* Count of delimitators */
        if (estado == 0) {
            if (c == '(') paren++;
            if (c == ')') paren--;
            if (c == '[') bracket++;
            if (c == ']') bracket--;
            if (c == '{') brace++;
            if (c == '}') brace--;
            
            
            if (paren < 0 || bracket < 0 || brace < 0) {
                printf("Error: delimitador de cierre sin apertura\n");
                error = 1;
                
                if (paren < 0) paren = 0;
                if (bracket < 0) bracket = 0;
                if (brace < 0) brace = 0;
            }
        }
        
        lastc = c;
    }
    
    
    if (estado == 1) {
        printf("Error: cadena sin cerrar\n");
        error = 1;
    }
    else if (estado == 2) {
        printf("Error: carácter sin cerrar\n");
        error = 1;
    }
    else if (estado == 3) {
        printf("Error: comentario sin cerrar\n");
        error = 1;
    }
    
    else if (paren > 0) {
        printf("Error: %d paréntesis sin cerrar\n", paren);
        error = 1;
    }
    else if (bracket > 0) {
        printf("Error: %d corchetes sin cerrar\n", bracket);
        error = 1;
    }
    else if (brace > 0) {
        printf("Error: %d llaves sin cerrar\n", brace);
        error = 1;
    }
    
    else if (error == 0) {
        printf("No se encontraron errores de sintaxis.\n");
    }
    
    return error;
}

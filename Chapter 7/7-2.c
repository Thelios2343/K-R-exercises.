#include <stdio.h>
#include <ctype.h>

#define MAXLEN 60

int main () {
    int c;
    int col;

    col = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar('\n');
            col = 0;
            continue;
        }
        if (isprint(c)) {
            putchar(c);
            col++;
        } else {
            switch (c) {
                case '\t' : 
                    printf("\\t");
                    col+= 2; 
                    break;
                case '\a' : 
                    printf("\\a"); 
                    col+= 2; 
                    break;
                case '\b' : 
                    printf("\\b"); 
                    col+= 2; 
                    break;
                case '\r' :
                    printf("\\r");
                    col+= 2; 
                    break;
                default:
                printf("\\0x%#02x", c);
                col += 6;
            }
        }

        /*Si se supera el maximo de linea Continua a otra linea*/
        if (col > MAXLEN) {
            putchar('\n'); 
            col = 0;
        }
    }
    return 0;
}

#include <stdio.h>

#define TABSTOP 8

int main (void) {
    
    int c;
    int col;
    int nspace;

    col = 0;
    nspace = 0;

    while ((c = getchar()) != EOF) {
        
        if (c == ' ') {
            ++nspace;
        } else {
            while (nspace > 0) {
                int to_tab = TABSTOP - (col % TABSTOP);

                if (nspace >= to_tab) {
                    putchar('\t');
                    col += to_tab;
                } 
                else {
                    putchar(' ');
                    ++col;
                    --nspace;
                }
            }

            putchar (c);

            if (c == '\n') {
                col = 0;
            } else if (c == '\t') {
                col += TABSTOP - (col % TABSTOP);
            }
            else {
                ++col;
            }
        }

    }
    
    return 0;
}

#include <stdio.h>

#define TABSTOP 8

int next_tab_stop(int col);
void print_spaces(int n);

int main () {

    int c;
    int col;

    col = 0;

    while ((c = getchar()) != EOF) {
        
        if ( c == '\t') {
            
            int spaces = next_tab_stop(col);
            print_spaces(spaces);
            col += spaces;
        }

        else if (c == '\n') {
            
            putchar(c);
            col = 0;

        }
        else {
            putchar(c);
            ++col;

        }
        
    }

}

int next_tab_stop (int col) {
    
    return TABSTOP - (col % TABSTOP);

}

void print_spaces(int n) {
    for (int i = 0; i < n; ++i) {
        putchar(' ');
    }
}

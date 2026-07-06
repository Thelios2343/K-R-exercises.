#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTABS 100  
#define DEFAULT 8     

int main(int argc, char *argv[]) {
    int tabs[MAXTABS];
    int i, pos, col;
    char c;
    int tab_count = 0;

    for (i = 0; i < MAXTABS; i++) {
        tabs[i] = 0;
    }

    if (argc == 1) {
        for (i = 0; i < MAXTABS; i++)
            tabs[i] = (i + 1) * DEFAULT;
        tab_count = MAXTABS;
    } else {
        for (i = 1; i < argc && tab_count < MAXTABS; i++) {
            pos = atoi(argv[i]);
            if (pos > 0)
                tabs[tab_count++] = pos;
        }
        if (tab_count == 0) {
            for (i = 0; i < MAXTABS; i++)
                tabs[i] = (i + 1) * DEFAULT;
            tab_count = MAXTABS;
        }
    }

    col = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int next_tab = 0;
            for (i = 0; i < tab_count; i++) {
                if (tabs[i] > col) {
                    next_tab = tabs[i];
                    break;
                }
            }
            if (next_tab == 0) {
                next_tab = ((col / DEFAULT) + 1) * DEFAULT;
            }
            while (col < next_tab) {
                putchar(' ');
                col++;
            }
        } else {
            putchar(c);
            col++;
            if (c == '\n')
                col = 0;
        }
    }
    return 0;
}

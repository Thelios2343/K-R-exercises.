#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
#define DEFAULT_TAB 8

int start = -1;   
int step = -1;    

int is_tab_stop(int col) {
    if (start > 0 && step > 0) {
        return (col >= start && (col - start) % step == 0);
    } else if (start > 0) {
        return (col == start);
    } else if (step > 0) {
        return (col % step == 0);
    } else {
        return (col % DEFAULT_TAB == 0);
    }
}

void entab(char *s) {
    int i, col = 0;
    int spaces = 0;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ') {
            spaces++;
            col++;
        } else {
            while (spaces > 0) {
                if (is_tab_stop(col - spaces)) {
                    putchar('\t');
                    spaces = 0;
                } else {
                    putchar(' ');
                    spaces--;
                }
            }
            putchar(s[i]);
            if (s[i] == '\n')
                col = 0;
            else
                col++;
        }
    }
}

int main(int argc, char *argv[]) {
    char line[MAXLINE];

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            start = atoi(argv[i] + 1);
        } else if (argv[i][0] == '+') {
            step = atoi(argv[i] + 1);
        }
    }

    while (fgets(line, MAXLINE, stdin) != NULL) {
        entab(line);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXWORD 100

static char buf[BUFSIZE];
static int bufp = 0;

/* Funciones de analisis lexico */
int getch(void);
void ungetch(int c);
int getword(char *word, int lim);

int getch (void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch (int c) {
    if (bufp >= BUFSIZE) {
        printf("Error: Too Many Chars");
    } else {
        buf[bufp++] = c;
    }
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    return 0;
}

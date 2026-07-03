#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: demasiados caracteres\n");
    else
        buf[bufp++] = c;
}

int getint(int *pn) {
    int c, sign, nextc;

    while (isspace(c = getch()))
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        nextc = getch();
        if (!isdigit(nextc)) {
            if (nextc != EOF) {
                ungetch(nextc);
            }

            ungetch(c);
            return 0;
        }

        c = nextc;
    }

    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    *pn *= sign;

    if (c != EOF) {
        ungetch(c);
    }

    return c;
}

int main() {
    int n, ret;

    printf("Introduce números (Ctrl+D para terminar):\n");
    while ((ret = getint(&n)) != EOF) {
        if (ret > 0) {
            printf("int: %d\n", n);
        } else if (ret == 0) {
            int c = getch();
            if (c == EOF) break;
            if (c == '+' || c == '-') {
                printf("Signo '%c'\n", c);
                int next = getch();
                if (next != EOF)
                    printf("Ignorado '%c'\n", next);
            } else {
                printf("'%c'\n", c);
            }
        }
    }
    printf("Fin.\n");
    return 0;
}

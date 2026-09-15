#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define BUFSIZE 100

/* Own Minimal Scanf */
int minscanf(char *srt, ...);

/* Lexer Funcs */
int look_int(char *str);
int look_float(char *str);
int getword(char *str, int lim);
int getch(void);
void ungetch(int c);


char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("Too Many Chars\n");
        return;
    } else
        buf[bufp++] = c;
}

int minscanf(char *srt, ...) {
    va_list ap;
    int *ival;
    char *cval;
    char *sval;
    float *fval;
    char *ptr;
    int count = 0;      

    char word[MAXWORD];

    va_start(ap, srt);
    for (ptr = srt; *ptr; ptr++) {
        if (*ptr == '%') {
            switch (*++ptr) {
                case 'd':
                    ival = va_arg(ap, int *);
                    getword(word, MAXWORD);
                    if (look_int(word)) {
                        *ival = atoi(word);
                        count++;
                    }
                    break;

                case 'f':
                    fval = va_arg(ap, float *);
                    getword(word, MAXWORD);
                    if (look_float(word)) {
                        *fval = strtof(word, NULL);
                        count++;
                    }
                    break;

                case 's':
                    sval = va_arg(ap, char *);
                    getword(word, MAXWORD);
                    strcpy(sval, word);
                    count++;
                    break;

                case 'c':
                    cval = va_arg(ap, char *);

                    {    
                        int c = getch();
                        if (c == EOF) {
                            va_end(ap);
                            return count;
                        }
                        *cval = (char)c;
                        count++;
                    }

                    break;

                default:
                    printf("Error (im lazy i'll make it a better message later)\n");
                    break;
            }
        } else if (isspace(*ptr)) {
            continue;
        }
    }
    va_end(ap);
    return count;
}

int look_int(char *str) {
    if (*str == '-' || *str == '+')
        str++;

    if (!isdigit(*str))
        return 0;

    while (isdigit(*str))
        str++;

    return *str == '\0';
}


int look_float(char *str) {
    char *endptr;
    if (*str == '\0')
        return 0;
    strtod(str, &endptr);
    return *endptr == '\0';
}

int getword(char *str, int lim) {
    int c;
    char *w = str;

    while (isspace(c = getch()))
        ;

    if (c == EOF) {
        str[0] = '\0';
        return EOF;
    }

    if (!isalnum(c) && c != '+' && c != '-') {
        str[0] = c;
        str[1] = '\0';
        return c;
    }

    *w++ = c;

    for (; --lim > 0; w++) {
        c = getch();
        if (!isalnum((unsigned char)c) && c != '.') {
            ungetch(c);
            break;
        }
        *w = c;
    }
    *w = '\0';

    return str[0];
}


int main(void) {
    char hh[MAXWORD];
    int n = 0;
    int readed;

    printf("Escribe un numero decimal y un string: ");
    readed = minscanf("%d %s", &n, hh);

    printf("Conversiones exitosas: %d\n", readed);
    printf("El Numero de mi scanf es %d y el string es %s\n", n, hh);
    return 0;
}

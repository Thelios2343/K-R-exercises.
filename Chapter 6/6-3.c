#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 100
#define MAXWORD 1000
#define MAXARRAY 1000

typedef struct tnode {
    char *word;
    struct lnode *lines;
    struct tnode *left;
    struct tnode *right;
} Tnode;

typedef struct lnode {
    int nline;
    struct lnode *next;
} Lnode;

const char *stop_words[] = {
    "a", "about", "an", "and", "are", "as", "at", "be",
    "by", "for", "from", "has", "he", "in", "is", "it",
    "of", "on", "or", "that", "the", "this", "to", "was",
    "we", "were", "will", "with", "you", "your", "i", "not"
};
size_t n_stop_words = sizeof(stop_words) / sizeof(stop_words[0]) ;

char buf[BUFSIZE];
int bufp = 0;

/* Funciones del lexer sencillo */
int getword(char *s, int lim);
void ungetch(int c);
int getch(void);
int getstop(char *w); 

/* Funciones del arbol */
Tnode *addtree(Tnode *p, char *w);
Tnode *talloc(void);


static int nline = 1;

int getword(char *s, int lim) {
    int c, d;
    char *w;

    for (;;) {
        w = s;

        while (isspace((unsigned char)(c = getch())))
            ;

        if (c == EOF) {
            *s = '\0';
            return EOF;
        }

        if (c == '/') {
            if ((d = getch()) == '*') {
                while ((c = getch()) != EOF) {
                    if (c == '*' && (d = getch()) == '/')
                        break;
                    else if (d != EOF)
                        ungetch(d);
                }
                continue;
            } else if (d == '/') {
                while ((c = getch()) != EOF && c != '\n')
                    ;
                continue;
            } else {
                if (d != EOF)
                    ungetch(d);
            }
        }

        break;
    }

    *w++ = c;
    /* Reservamos un char para el '\0' final desde ya */
    lim--;

    if (c == '"') {
        while ((c = getch()) != EOF && c != '"') {
            if (c == '\\') {
                getch();
            } else if (lim > 1) {
                *w++ = c;
                lim--;
            }
        }
    } else if (c == '\'') {
        while ((c = getch()) != EOF && c != '\'') {
            if (c == '\\') {
                getch();
            } else if (lim > 1) {
                *w++ = c;
                lim--;
            }
        }
    } else if (isalpha((unsigned char)c) || c == '_') {
        for ( ; --lim > 0; w++) {
            c = getch();
            if (!isalnum((unsigned char)c) && c != '_') {
                ungetch(c);
                break;
            }
            *w = c;
        }
    }

    *w = '\0';
    return s[0];
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("error: too many chars\n");
    } else {
        buf[bufp++] = c;
    }
}

int getstop(char *s) {
    int i;

    for (i = 0; i < n_stop_words; i++) {
        if(!strcmp(s, stop_words[i])) {
            return 1;
        }
    }
    return 0;
}

Tnode *addtree(Tnode *p, char *w) {
    return 0;
}

Tnode *talloc(void) {
    return malloc(sizeof(Tnode));
}

int main () {
    Tnode *root;
    char word[MAXWORD];

    root = NULL;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && !getstop(word)) {
            return 0;
        } else {
            return 0;
        }
    }
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;
/*variables de buffer*/

int getword(char *word, int lim);
int getch(void);
void ungetch(int);
/*Prototipos de funciones*/


int main() {
    char word[MAXWORD];
    int c;

        while ((c = getword(word, MAXWORD)) != EOF) {
            if (isalpha(c) || c == '_') {
                printf("Palabra: %s\n", word);
        }
    }

    return 0;
}

int getch (void) {
    return (bufp < 0) ? buf[--bufp] : getchar();  
}

void ungetch(int c) {

    if (bufp > BUFSIZE) {
        printf("Demasiados caracteres \n");
    } 
    else {
        buf[bufp++] = c;
    } 

} 


int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    if (c == '/') {
        if ((d = getch()) == '*') {  
            while ((c = getch()) != EOF) {
                if (c == '*' && (d = getch()) == '/')
                    break;
                ungetch(d);  
            }
            *w = '\0';
            return getword(word, lim); 
        } else if (d == '/') {  
            while ((c = getch()) != EOF && c != '\n')
                ;
            *w = '\0';
            return getword(word, lim);
        } else {
            ungetch(d);
            *w = '\0';
            return c;
        }
    }

    if (c == '\"') {
        while ((c = getch()) != EOF && c != '\"') {
            if (c == '\\')  
                getch();
        }
        *w = '\0';
        return '\"';
    }

    if (c == '\'') {
        while ((c = getch()) != EOF && c != '\'') {
            if (c == '\\')
                getch();
        }
        *w = '\0';
        return '\'';
    }

    if (c == '#') {
        while ((c = getch()) != EOF && c != '\n')
            ;
        *w = '\0';
        return getword(word, lim);
    }

    if (isalpha(c) || c == '_') {
        for ( ; --lim > 0; w++) {
            if (!isalnum(*w = getch()) && *w != '_') {
                ungetch(*w);
                break;
            }
        }
        *w = '\0';
        return word[0];
    }

    *w = '\0';
    return c;
}

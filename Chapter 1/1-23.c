#include <stdio.h>

/* This Program is kinda tricky lmao cuzz i had to define states for every cases i did that with an enum for the states and i called acording the situation */

enum State {
    NORMAL,
    IN_COMMENT,
    IN_STRING,
    IN_CHAR
};

int main(void)
{
    int c, d;
    enum State state = NORMAL;

    while ((c = getchar()) != EOF) {

        if (state == NORMAL) {
            if (c == '/') {
                d = getchar();
                if (d == '*') {
                    state = IN_COMMENT;
                } else {
                    putchar(c);
                    if (d != EOF)
                        putchar(d);
                }
            } else if (c == '"') {
                state = IN_STRING;
                putchar(c);
            } else if (c == '\'') {
                state = IN_CHAR;
                putchar(c);
            } else {
                putchar(c);
            }
        }

         /* block of conditionals that evaluate states and execute depending on the state at that moment */
        else if (state == IN_COMMENT) {
            if (c == '*') {
                d = getchar();
                if (d == '/')
                    state = NORMAL;
                else if (d != EOF)
                    ungetc(d, stdin);
            }
        }

        
        else if (state == IN_STRING) {
            putchar(c);
            if (c == '\\') {
                d = getchar();
                if (d != EOF)
                    putchar(d);
            } else if (c == '"') {
                state = NORMAL;
            }
        }

        else if (state == IN_CHAR) {
            putchar(c);
            if (c == '\\') {
                d = getchar();
                if (d != EOF)
                    putchar(d);
            } else if (c == '\'') {
                state = NORMAL;
            }
        }
    }

    return 0;
}


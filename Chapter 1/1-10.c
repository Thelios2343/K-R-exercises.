#include <stdio.h>

int main () {

    
int c;

    while ((c = getchar()) != EOF ) {
   

                putchar(c);

                if (c == '\t') {

                    putchar('\\');
                    putchar('t');
                }

                else if (c == '\b') {

                    putchar ('\\');
                    putchar ('b');

                }

                else if (c == '\\') {

                    putchar('\\');
                    putchar('/');


                }

    }


return 0;

}



#include <stdio.h>


int main () {


    int nl, tab, blank;

    int c;

    nl = 0;
    tab = 0;
    blank = 0;


    while ((c = getchar()) != EOF) {

            if ( c == '\n') { 

            ++ nl;

            }

            else if (c == '\t') {

            ++ tab;


            }

            else if (c == ' ') {
                
            ++ blank;
                

            }
            

            }


    printf ("\n nuevas lineas : %d\n tabulaciones : %d\n espacios en blanco : %d\n", nl, tab, blank);
            


}


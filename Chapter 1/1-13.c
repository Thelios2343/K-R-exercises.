#include <stdio.h>

#define OUT 0
#define IN 1
#define MAX 20


int main (){

    int c, state, len;

    int word_len_count[MAX + 1];

    state = OUT;
    len = 0;

    int i;

    for ( i = 1; i <= MAX; ++i) 
        word_len_count[i] = 0;


    while ((c = getchar()) != EOF ) {


        if (c == ' ' || c == '\n' || c == '\t') {

            if (state == IN) {

                if (len > MAX)
                    len = MAX;

               ++word_len_count[len];

               len = 0;

            }

            state = OUT;
                
        } 

        else {

            state = IN;
            ++len;
        }
    }


    
if (state == IN) {

    if (len > MAX) 
        len = MAX;
    ++word_len_count[len];
}

printf ("\nHistoriograma de longitud\n");
    for (int i = 1; i <= MAX; ++i) {

        printf("%2d:", i);

        for (int j = 0; j < word_len_count[i]; ++j)
            
        printf("#");
        printf("\n");

    }
    


return 0;

}

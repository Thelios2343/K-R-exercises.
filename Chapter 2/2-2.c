#include <stdio.h>
#define LIM 100 

int main(void) {
    
    int i ;
    char c;
    char s[LIM];
    int lim;
    lim = LIM;

    for (i = 0; i < lim - 1; ++i) {
        
        if ((c = getchar()) == '\n')
            break;
        if (c == EOF)
            break;
        s[i] = c;
    }

    s[i] = '\0';

    printf("Leido: %s\n", s);
        return 0;
    

}

#include <stdio.h>

#define MAX_CHAR 128

int main () {

    int c;
    int freq[MAX_CHAR] = {0};


    while ((c = getchar()) != EOF) {
        if (c >= 0 && c < MAX_CHAR) 
            ++freq[c];

    } 

    for (int i = 0; i < MAX_CHAR; ++i) {
        if (freq[i] > 0) {
            printf("2%d ('%c') | ", i, (i >= 32 && i <= 126 ? i : ' '));
            for (int j = 0; j < freq[i]; ++j)
                putchar('#');
            putchar('\n');

        }
        

    }

return 0;

}

#include <stdio.h>

int same_type (char a, char b);
void expand (char s1[], char s2[]);

int same_type (char a, char b) {
       
    /* minúsculas */
    if (a >= 'a' && a <= 'z' &&
        b >= 'a' && b <= 'z'){
        return 1;
    }
    /* mayúsculas */
    if (a >= 'A' && a <= 'Z' &&
        b >= 'A' && b <= 'Z') {
        return 1;
    }
    /* dígitos */
    if (a >= '0' && a <= '9' &&
        b >= '0' && b <= '9') {
        return 1;
    }

    return 0;
}

void expand (char s1[], char s2[]) {
    
    int i = 0;
    int j = 0;
    char c;

    while (s1[i] != '\0') {

        if (
            s1[i] == '-' &&
            i > 0 &&
            s1[i + 1] != '\0' &&
            same_type(s1[i - 1], s1[i + 1]) &&
            s1[i - 1] <= s1[i + 1]) {


            for (c = s1[i - 1] + 1;
                 c < s1[i + 1];
                 c++) {

                s2[j++] = c;
            }
        } 

        else {

            s2[j++] = s1[i];
        }   

        i++;
    }
    s2[j] = '\0';
}




int main () {
    
    char s1[] = "a-z";
    char s2[200];

    expand(s1, s2);

    printf("\n%s\n", s2);

    return 0;
}

#include <stdio.h>

void itoa (int n, char s[], int *i);

int main () {
    char s[10];
    int n = 1203;
    int i = 0;
    
    itoa(n, s, &i);
    s[i] = '\0';  
    
    printf("El número %d convertido a string es: %s\n", n, s);
    
    return 0;
}

void itoa (int n, char s[], int *i) {
    if (n / 10) {
        itoa(n / 10, s, i);
    }
    s[(*i)++] = n % 10 + '0';
}

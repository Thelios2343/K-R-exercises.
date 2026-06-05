#include <stdio.h>

void my_reverse (char *s);
int abs (int n);
void itoa (int n, char s[], int t); 

int main () {
    
    int n = 15;
    char s[100];
    int t = 100;

    itoa(n, s, t);

    printf("%s", s); 
}

void itoa (int n, char s[], int t) {
    
    int i, sign, j;
    sign = n;

    i = 0;

    
    do { 
        s[i++] = abs(n % 10) + '0';

    } while((n /= 10) != 0); 
    
    if (sign < 0) {
        s[i++] = '-';
    }

    for (j = 0; j < t; j++) {
        s[i++] = ' ';
    } 

    s[i] = '\0';

    my_reverse(s);
}

int abs (int n) {
    
    if (n < 0) {
        return -n;
    } else {
        return n;
    }
}

void my_reverse (char *s) {
    
    char *end = s;
    char temp;

    while (*end != '\0') {
        end++;
    }

    end--;

    while (s < end) {
        
        temp = *s;
        *s = *end;
        *end = temp;

        s++;
        end--;
    }
}

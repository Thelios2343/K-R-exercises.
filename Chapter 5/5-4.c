#include <stdio.h>

int str_len(char *s);
int strend(char *s, char *t);

int main () {
    
    char s[100] = "Programa";
    char t[100] = "ma";

   printf("%d\n", strend(s, t) );

    return 0;
}

int str_len(char *s) {
    int n = 0;
    while (*s != '\0') {
        s++;
        n++;
    }
    return n;
}

int strend(char *s, char *t) {
   
    if (str_len(t) > str_len(s)) {
        return 0;
    }

    s += str_len(s) - str_len(t);
    
    while (*t != '\0') {
        

        if (*s != *t) {
            return 0;
        }

        s++;
        t++;
    }

    return 1;
}

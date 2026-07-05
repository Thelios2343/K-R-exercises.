#include <stdio.h>

void str_cpy(char *s, char *t, int n);
int str_len(char *s);

int main () {
    
    char s[100];
    char t[100] = "hola";

    str_cpy(s, t, 3);

    printf("%s", s);

    return 0;
}

int str_len (char *s) {
    int n = 0;

    while (*s != '\0') {
        s++;
        n++;
    }

    return n;
}

void str_cpy(char *s, char *t, int n) {
   int i;
  

   for (i = 0; i < n; i++) { 
        *s = *t;
         s++;
         t++;
   }
   *s = '\0';

}

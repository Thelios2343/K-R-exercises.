#include <stdio.h>

void my_escape(char s[], char t[]);

int main() {

   char s[100];
   char t[] = "Hola\tmundo";


    my_escape(s,t);

    printf("%s", s);


}

void my_escape(char s[], char t[]) {
    int i;
    int j;

    for (i = 0, j = 0; t[i] != '\0'; ++i) {
        
        switch (t[i]) {
            
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
        }
    }
s [j] = '\0';
}

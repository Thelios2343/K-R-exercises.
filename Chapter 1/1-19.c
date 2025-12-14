#include <stdio.h>
#define MAXLINE 1000

int get_line (char s[], int lim);
void reverse (char s[]);

int main () {


char line[MAXLINE];

while (get_line(line, MAXLINE) > 0) {

    reverse(line);

    printf("la palabra invertida es: %s\n", line);
}

return 0;

}



void reverse (char s[]) {

    int i, j;
    char temp;

    for (j = 0; s[j] != '\0'; j++);

    --j;


    for (i = 0; i < j; ++i, --j) {
    
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;

    }

}

int get_line(char s[], int lim) {

    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) 
        s[i] = c;

    if (c == '\n') {

        s[i] = c;
        ++i;

    }

    s[i] = '\0';
    
    return i;

}

#include <stdio.h>

int strindex (char s[], char t[]);

int main () {
    
    char line[100] = "Hola dia, dia malo";
    char patron[100] = "dia";
    int pos;

    pos = strindex(line, patron);
    printf ("%d\n", pos);

    return 0;

}


int strindex (char s[], char t[]) {
    
    int i, j, k;
    int position = -1;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {
        }
            if (k > 0 && t[k] == '\0') {
                position = i;
            }
    }
    
    return position;
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char c;

if (argc > 1) {
    printf("Use: ./tolower / ./toupper\n");
    return 0;
}
    while ((c = getchar()) != EOF) {
        if (strcmp(argv[0], "./toupper") == 0) {
            putchar(toupper(c));
        } else if (strcmp(argv[0], "./tolower") == 0) {
            putchar(tolower(c)); 
        } else {
            printf("Use: ./tolower / ./toupper\n");
            return 0;
        }
    }
    return 0;
}

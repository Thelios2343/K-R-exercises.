#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char c;

if (argc == 2) { 

    while ((c = getchar()) != EOF) {
        if (strcmp(argv[1], "-toupper") == 0) {
            putchar(toupper(c));
        } else if (strcmp(argv[1], "-tolower") == 0) {
            putchar(tolower(c)); 
        } else { 
            printf("Use: ./a.out -tolower / -toupper\n");
            return 0;
        }
    }
}
else{
    printf("Use: ./a.out -tolower / -toupper\n");
}
    return 0;
}

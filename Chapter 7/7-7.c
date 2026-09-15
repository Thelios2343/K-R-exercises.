#include <stdio.h>
#include <string.h>

#define MAXWORD 100

char buffer[MAXWORD];
char line[MAXWORD];

int main(int argc, char *argv[]) {

    if (argc == 1 || argc > 3) {
        printf("Error, Usage ./Programa argv1 = archive argv2 = pattern\n");
    } else if (argc == 2) {
        FILE *a;
        
        if((a = fopen(argv[1], "r")) == NULL)
            return 0;
        else {
            fgets(buffer, sizeof(buffer), stdin);

            while(fgets(line, sizeof line, a) != NULL) {
                if(strstr(line, buffer) != NULL)
                    printf("%s\n", line);
            } 
        }
    } else if (argc == 3) {
        FILE *a;
        FILE *b;

        if((a = fopen(argv[1], "r")) == NULL || (b = fopen(argv[2], "r")) == NULL) 
            return 0;
        else {
            fgets(buffer, sizeof(buffer), b);

            while(fgets(line, sizeof line, a) != NULL) {
                if(strstr(line, buffer) != NULL)
                    printf("%s\n", line);
            }
        }
            
    }

    return 0;
}

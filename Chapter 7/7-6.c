#include <stdio.h>
#include <string.h>

#define MAXWORD 100

int file1 = 1;
int file2 = 1;

void get_line(char *str);
void printnline(FILE *str, int n);

void printnline(FILE *str, int n) {
    int line = 1;
    int c;                     
    int i = 0;

    char buffer[MAXWORD];

    rewind(str);                

    while (line != n) {
        c = fgetc(str);
        if (c == EOF) {          
            buffer[0] = '\0';
            printf("%s", buffer);
            return;
        }
        if (c == '\n') {
            line++;
        }
    }

    while ((c = fgetc(str)) != '\n' && c != EOF && i < MAXWORD - 1) {
        buffer[i++] = c;
    }
    buffer[i] = '\0';            
    printf("%s", buffer);
}

int main() {
    FILE *a = fopen("archivo1.txt", "r");
    FILE *b = fopen("archivo2.txt", "r");

    if (a == NULL || b == NULL) {
        perror("fopen");
        return 1;
    }

    int ca, cb;

    while((ca = fgetc(a))!= EOF && (cb = fgetc(b)) != EOF) {
        if (ca == '\n') {
            file1++;
        } 
        if (cb == '\n') {
            file2++;
        }

        if (ca != cb) {
            printf("no son iguales\n");
            printnline(a, file1);
            printf(" %d", file1);
            printf("\n");
            printnline(b, file2);
            printf(" %d", file2);
            printf("\n");
            fclose(a);
            fclose(b);
            return 0;
        }
    }

if(ca == cb) 
    printf("Son Iguales\n");
else
    printf("Son Distintos\n");

fclose(a);
fclose(b);

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 100    
#define MAXLEN   1000   
#define DEFAULT_N 10

int my_getline(char *line, int maxlen);

char buf[MAXLINES][MAXLEN];   

int main(int argc, char *argv[])
{
    int n = DEFAULT_N;

    if (argc > 1) {
        n = atoi(argv[1]);
        if (n <= 0 || n > MAXLINES) {
            fprintf(stderr, "uso: tail [-n], con 0 < n <= %d\n", MAXLINES);
            return 1;
        }
    }

    char line[MAXLEN];
    int count = 0;   
    int pos = 0;     
    int len;

    while ((len = my_getline(line, MAXLEN)) > 0) {
        strcpy(buf[pos], line);
        pos = (pos + 1) % n;
        count++;
    }

    int start, total;
    if (count < n) {
        start = 0;
        total = count;
    } else {
        start = pos;
        total = n;
    }

    for (int i = 0; i < total; i++) {
        int idx = (start + i) % n;
        printf("%s", buf[idx]);
    }

    return 0;
}

int my_getline(char *line, int maxlen)
{
    int c, i;
    for (i = 0; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}

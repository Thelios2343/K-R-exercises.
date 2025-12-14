#include <stdio.h>

#define MAXLINE 1024

int getline_clean(char line[], int maxline);
int remove_trailing(char line[]);

int main(void)
{
    char line[MAXLINE];
    int len;

    while ((len = getline_clean(line, MAXLINE)) > 0) {
        len = remove_trailing(line);

        if (len > 0) {   
            printf("%s", line);
        }
    }

    return 0;
}


int getline_clean(char line[], int maxline)
{
    int c, i;

    for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;

    if (c == '\n') {
        line[i] = c;
        i++;
    }

    line[i] = '\0';
    return i;
}


int remove_trailing(char line[])
{
    int i = 0;

    while (line[i] != '\0')
        i++;

    i--;  

    
    while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i--;

    
    if (i >= 0) {
        line[i + 1] = '\n';
        line[i + 2] = '\0';
        return i + 2;
    }

    return 0;  
}


#include <stdio.h>

#define MAXLINE 1000   

int getline_kr(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
    int len;              
    int total_len;        
    int max = 0;          
    char line[MAXLINE];  
    char longest[MAXLINE];

    while ((len = getline_kr(line, MAXLINE)) > 0) {
        total_len = len;

        
        while (line[len - 1] != '\n' &&
               (len = getline_kr(line, MAXLINE)) > 0) {
            total_len += len;
        }

        if (total_len > max) {
            max = total_len;
            copy(longest, line); 
        }
    }

    if (max > 0) {
        printf("Longitud: %d\n", max);
        printf(":\n%s", longest);
    }

    return 0;
}


int getline_kr(char s[], int lim)
{
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


void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}


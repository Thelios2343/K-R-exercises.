#include <stdio.h>
#include <stdlib.h>  
#include <math.h>    
#include <string.h>  

#define MAXOP 100    
#define MAXLINE 100  
#define NUMBER '0'   

int getop(char **p, char *s);
void push(double f);
double pop(void);
void clear(void);
int get_line(char s[], int lim);

double val[MAXOP];   
int sp = 0;          


int main(void) {
    int type;
    double op2;
    char s[MAXOP];
    char line[MAXLINE];
    
    while (get_line(line, MAXLINE) > 0) {
        char *p = line;  
        
        while ((type = getop(&p, s)) != '\0') {
            switch (type) {
                case NUMBER:
                    push(atof(s));
                    break;
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        printf("Error: división por cero\n");
                    break;
                case '%':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(fmod(pop(), op2));
                    else
                        printf("Error: división por cero en %%\n");
                    break;
                case '\n':
                    printf("\t%.8g\n", pop());
                    break;
                default:
                    printf("Error: comando desconocido %s\n", s);
                    break;
            }
        }
    }
    return 0;
}

int getop(char **p, char *s) {
    int i;
    char *line = *p;
    
    while (*line == ' ' || *line == '\t')
        line++;
    
    if (*line == '\0' || *line == '\n') {
        *p = line;
        return '\0';
    }
    
    i = 0;
    s[i] = *line;
    
    if ((*line >= '0' && *line <= '9') || *line == '.') {
        i++;
        line++;
        while ((*line >= '0' && *line <= '9') || *line == '.')
            s[i++] = *line++;
        s[i] = '\0';
        *p = line;
        return NUMBER;
    }
    
    i++;
    line++;
    s[i] = '\0';
    *p = line;
    return s[0];
}

void push(double f) {
    if (sp < MAXOP)
        val[sp++] = f;
    else
        printf("Error: pila llena, no se puede apilar %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("Error: pila vacía\n");
        return 0.0;
    }
}

void clear(void) {
    sp = 0;
}

int get_line(char s[], int lim) {
    int c, i;
    
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    
    if (c == '\n')
        s[i++] = c;
    
    s[i] = '\0';
    return i;
}

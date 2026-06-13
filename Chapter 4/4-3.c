#include <stdio.h>
#include <stdlib.h>   /* para atof() */
#include <ctype.h>
#include <math.h>     /* para fmod() */

#define MAXOP   100   /* tamaño máximo de operando/operador */
#define NUMBER  '0'   /* señal de que se encontró un número */

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int c);

int main(void)
{
    int type;
    double op1, op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
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
                printf("error: división por cero\n");
            break;
        case '%':                       
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2)); 
            else
                printf("error: módulo por cero\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: comando desconocido %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100  

int sp = 0;          
double val[MAXVAL];  


void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: pila llena, no se puede pushear %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: pila vacía\n");
        return 0.0;
    }
}

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;      

    i = 0;
    if (c == '-') {    
        if (!isdigit(s[++i] = c = getch()) && c != '.') {
            ungetch(c);
            return '-';
        }
    }

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}


#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: demasiados caracteres\n");
    else
        buf[bufp++] = c;
}

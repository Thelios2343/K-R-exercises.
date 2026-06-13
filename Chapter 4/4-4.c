#include <stdio.h>
#include <stdlib.h>   
#include <ctype.h>
#include <string.h>    
#include <math.h>    

#define MAXOP   100   
#define NUMBER  '0'   
#define COMMAND 'c'    
#define MAXVAL 100    
#define BUFSIZE 100

extern int sp;
extern double val[];

int getop(char []);
void push(double);
double pop(void);
void clear_stack(void);  
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
        case COMMAND:                    
            if (strcmp(s, "print") == 0) {
                if (sp > 0)
                    printf("\t%.8g\n", val[sp-1]);
                else
                    printf("error: pila vacía\n");
            } else if (strcmp(s, "dup") == 0) {
                if (sp > 0) {
                    op1 = pop();
                    push(op1);
                    push(op1);
                } else
                    printf("error: dup necesita un elemento\n");
            } else if (strcmp(s, "swap") == 0) {
                if (sp >= 2) {
                    op1 = pop();
                    op2 = pop();
                    push(op1);
                    push(op2);
                } else
                    printf("error: swap necesita dos elementos\n");
            } else if (strcmp(s, "clear") == 0) {
                clear_stack();
            } else {
                printf("error: comando desconocido %s\n", s);
            }
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

void clear_stack(void)
{
    sp = 0;
}

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (islower(c)) {
        i = 0;
        while (islower(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        return COMMAND;
    }

    if (!isdigit(c) && c != '.' && c != '-')
        return c;      

    i = 0;

    if (c == '-') {
        c = getch();
        if (!isdigit(c) && c != '.') {
            ungetch(c);
            return '-';
        }
        s[++i] = c;
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

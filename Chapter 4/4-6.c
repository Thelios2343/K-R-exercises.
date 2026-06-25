#include <stdio.h>
#include <stdlib.h>  
#include <math.h>    
#include <ctype.h>   

#define MAXOP 100   
#define NUMBER '0'  
#define VARIABLE 'v' 
#define ASIGNAR '='  

int getop(char []);
void push(double);
double pop(void);
double top(void);    
void clear(void);

double variables[26];    
double ultimo = 0.0;     

int main()
{
    int tipo;
    double op2;
    char s[MAXOP];
    

    while ((tipo = getop(s)) != EOF) {
        switch (tipo) {
        case NUMBER:
            push(atof(s));
            break;

        case VARIABLE:
            push(variables[s[0] - 'a']);
            break;

        case ASIGNAR:
            if (s[0] >= 'a' && s[0] <= 'z') {
                op2 = pop();
                variables[s[0] - 'a'] = op2;
                push(op2);   
            } else {
                printf("error: variable no válida\n");
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
                printf("error: división por cero\n");
            break;

        case '?':  
            printf("\t%.8g\n", top());
            break;

        case 'c':  
            clear();
            break;

        case 'p':  
            printf("\t%.8g\n", ultimo);
            break;

        case '\n':
            ultimo = pop();
            printf("\t%.8g\n", ultimo);
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
        printf("error: pila llena, no se puede meter %g\n", f);
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

double top(void)
{
    if (sp > 0)
        return val[sp-1];
    else {
        printf("error: pila vacía\n");
        return 0.0;
    }
}

void clear(void)
{
    sp = 0;
}



int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getchar()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (!isdigit(c) && c != '.' && !isalpha(c)) {
        return c;   
    }

    i = 0;

    if (isalpha(c)) {
        s[i] = c;
        s[++i] = '\0';

        c = getchar();
        if (c == '=') {
            s[i-1] = '=';   
            s[i] = '\0';
            return ASIGNAR;
        } else {
            ungetc(c, stdin);  
            return VARIABLE;
        }
    }

    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getchar()))
            ;
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = getchar()))
            ;
    }
    s[i] = '\0';
    if (c != EOF)
        ungetc(c, stdin);

    return NUMBER;
}

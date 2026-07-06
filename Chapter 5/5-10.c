#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STACK 100

void push(int valor);
int pop(void);

/*Variables globales*/

int stack[MAX_STACK];
int sp = 0;


int main (int argc, char *argv[]) {
    int i, op1, op2, resultado;

    if (argc < 2) {
        printf("Uso: expr [operando1] [operando2] ... [operador]\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {

        if (isdigit(argv[i][0]) || (((argv[i][0] == '+') || (argv[i][0] == '-')) && isdigit(argv[i][1]))) { 

            push(atoi(argv[i]));
        }
        else {
            op2 = pop();
            op1 = pop();

            switch (argv[i][0]) {
                case '+':
                    resultado = op1 + op2;
                    break;
                case '-':
                    resultado = op1 - op2;
                    break;
                case 'x':
                    resultado = op1 * op2;
                    break;
                case '/':
                    if (op2 != 0) {
                        resultado = op1 / op2;
                    }
                    else {
                        printf("Imposible dividir entre 0");
                        return 1;
                    } 
                    break;
                
                default:
                    printf("Operador: %s no valido\n", argv[i]);
                    return 1;
            }
            push(resultado);
        }
    }

    if (sp != 1) {
        printf("Error expresion incorrecta:\n");
        return 1;
    }

    printf("%d\n", pop());

    return 0;
}

void push(int valor) {
    if (sp < MAX_STACK)
        stack[sp++] = valor;
    else {
        printf("Error: pila llena\n");
        exit(1);
    }
}

int pop(void) {
    if (sp > 0) {
        return stack[--sp];
    }
    else {
        printf("Error: la pila está vacia\n");
        exit(1);
    }
}








#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAX_LINE 1000

int getfloat(float *pn);

int main() {
    float num;
    int estado;

    printf("Ingrese numeros reales (Ctrl+D para terminar):\n");
    while ((estado = getfloat(&num)) != EOF) {
        if (estado == 1)
            printf("leido: %g\n", num);
        else if (estado == 0)
            printf("No es un numero\n");
    }

    return 0;
}

int getfloat(float *pn) {
    int c, sign, signo_exp;
    float potencia = 1.0;
    int n = 0;
    float val = 0.0;
    int exp_val = 0;

    while (isspace(c = getchar()))
        ;

    if (c == EOF) {
        *pn = 0;
        return EOF;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '-' || c == '+') {
        c = getchar();
        if (!isdigit(c)) {
            ungetc(c, stdin);
            *pn = 0;
            return 0;
        }
    }

    for (val = 0; isdigit(c); c = getchar()) {
        val = 10 * val + (c - '0');
    }

    if (c == '.') {
        c = getchar();
        for (; isdigit(c); c = getchar()) {
            val = 10 * val + (c - '0');
            n++;
        }
        while (n-- > 0)
            potencia *= 10.0;
        val = val / potencia;
    }

    if (c == 'e' || c == 'E') {
        c = getchar();
        signo_exp = (c == '-') ? -1 : 1;
        if (c == '-' || c == '+')
            c = getchar();
        for (exp_val = 0; isdigit(c); c = getchar()) {
            exp_val = 10 * exp_val + (c - '0');
        }

        if (signo_exp == -1) {
            val /= pow(10, exp_val);
        }
        else {
            val *= pow(10, exp_val);
        }

    }

    *pn = sign * val;

    if (c == EOF) {
        return EOF;
    }
    else {
        return 1;
    }
}

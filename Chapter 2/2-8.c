#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main () {

    unsigned valor;

    valor = rightrot(9, 256);

    printf("El valor de la funcion es %u", valor);

}



unsigned rightrot(unsigned x, int n)
{
    int wordsize = sizeof(x) * 8;

    unsigned right = x >> n;

    unsigned wrapped =
        (x & ((1 << n) - 1)) << (wordsize - n);

    return right | wrapped;
}

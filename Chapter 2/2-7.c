#include <stdio.h>

unsigned invert (unsigned x, int p, int n) ;

int main () {
    
    unsigned bits;
    bits = invert(10, 3, 8);

    printf("Esto es el resultado de la funcion invert: %u\n", bits);

}

unsigned invert (unsigned x, int p, int n) {
    unsigned mask = ((1 << n) - 1) >> (p - n + 1);

    return x ^ mask;
}

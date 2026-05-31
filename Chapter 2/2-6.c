#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    
    unsigned mask = (1 << n) - 1;
    
    unsigned ybits = y & mask;

    ybits <<= p;

    unsigned clear_mask = mask << p;    
    x = x & ~clear_mask;

    return x | ybits;
}


int main () {

    unsigned x = 0b00010010;
    unsigned y = 0b00010111;
    int p = 4;
    int n = 3;

    unsigned resultado = setbits(x, p, n, y);

    printf("x =  (binario: ");
    for (int i = 7; i >= 0; i--) printf("%d", (x >> i) & 1);
    printf(")\n");
    
    printf("y =  (binario: ");
    for (int i = 7; i >= 0; i--) printf("%d", (y >> i) & 1);
    printf(")\n");
    
    printf("Resultado =  (binario: ");
    for (int i = 7; i >= 0; i--) printf("%d", (resultado >> i) & 1);
    printf(")\n");
    
    return 0;
    
}

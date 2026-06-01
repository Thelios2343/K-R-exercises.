#include <stdio.h>

int bitcount(unsigned x);

int main () {
    
    printf("El resultado de la funcion bitcount: %d", bitcount(32));
    
}

int bitcount(unsigned x) {
    
    int count = 0;

/* --- EStE es la version mas rapida siendo una unica iteracion por bit positico --- */

    while (x) {
        x &= (x - 1);
        ++count;
    }

return count;

} 

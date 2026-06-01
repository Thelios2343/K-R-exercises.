#include <stdio.h>

int binsearch(int x, int v[], int n);

int main () {
    int v[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,19,22, 25};
    int x = 25;
    int n = sizeof(v) / sizeof(v[0]); 

    int resultados = binsearch(x, v, n);

    if (resultados != -1) {
        printf("El numero que buscas fue encontrado en el arreglo en la posicion: %d\n", resultados);
    }
    else {
        printf("No se encontro el elemento");
    }

}


int binsearch(int x, int v[], int n) {
    
    int low, high, mid;
    low = 0;
    high = n-1;

    while (low <= high) {
        mid = low + (high - low) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    if (v[low] == x) {
        return low;
    }

    return -1;

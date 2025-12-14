#include <stdio.h>

int main () {

    float fahr, celsius;


    int lower, upper, step;

    lower = 0;
    upper = 400;
    step = 20;

    fahr = lower;

    printf ("Convertidor de grados fahrenheit a Celsius\n");

    while (fahr <= upper) {

        celsius = (5.0/9.0) * (fahr - 32.0);

        printf ("%14.0f\t%6.1f\n", fahr, celsius );

        fahr = fahr + step;
    }
    



} 

#include <stdio.h>

int main () {

    int upper, lower, step;

    lower = 0;
    upper = 300;
    step = 20;

    float fahr, celsius;

    celsius = lower;


    while (celsius <= upper) {

        fahr = (celsius * 1.8) + 32;

            printf ("%5.0f\t%3.2f\n", celsius, fahr);

        celsius = celsius + step;




    }


}

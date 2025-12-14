#include <stdio.h>

float fahr_to_celsius(float fahr);

int main () {
    
    int upper, lower, step;

    lower = 0;
    upper = 300;
    step = 10;
    float fahr;
    fahr = lower;

    while (fahr <= upper) {

        printf("%5.0f\t%3.2f\n", fahr, fahr_to_celsius(fahr));
    fahr += step;

    }

return 0;

}


float fahr_to_celsius(float fahr) {

    return (5.0/9.0) * (fahr - 32.0);

}

#include <stdio.h>


int lower (int c);

int main () {

    char c = 'B';

    printf("En minuscula es %c", lower (c));

}

int lower (int c) {
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A': c;
}

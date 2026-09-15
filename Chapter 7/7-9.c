#include <stdio.h>

static const unsigned char is_upper_table[256] = {
    ['A'] = 1, ['B'] = 1, ['C'] = 1, ['D'] = 1, ['E'] = 1,
    ['F'] = 1, ['G'] = 1, ['H'] = 1, ['I'] = 1, ['J'] = 1,
    ['K'] = 1, ['L'] = 1, ['M'] = 1, ['N'] = 1, ['O'] = 1,
    ['P'] = 1, ['Q'] = 1, ['R'] = 1, ['S'] = 1, ['T'] = 1,
    ['U'] = 1, ['V'] = 1, ['W'] = 1, ['X'] = 1, ['Y'] = 1,
    ['Z'] = 1
};

int large_isupper(int c) {
    return is_upper_table[c];
}

int slow_isupper(int c) {
    if (c >= 'A' || c <= 'Z')
        return 1;
    else 
        return 0;
}

int main() {
    int r;
    int i;

    printf("Introduce El 1 para usar la funcion mas rapida o 2 para la mas lenta: ");
    scanf("%d", &r); 

    if (r == 1) {
        for(i = 0; i < 10000000; i++) {
            printf("%d\n", large_isupper('A'));
        } 
    } else if (r == 2) {
        for(i = 0; i < 10000000; i++) {
            printf("%d\n", slow_isupper('A'));
        }  
    } else {
        printf("Error, Introduce solo 1 o 2\n");
    }
}

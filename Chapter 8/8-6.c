#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *mycalloc(size_t number, size_t size);

int main () {
    char *c = mycalloc(5, sizeof c);
    int i;

    for (i = 0; i < 5; i++) {
        printf("%d\n", *c);
        c++;
    }
    return 0;
}

void *mycalloc(size_t number, size_t size) {
    void *tmp;
    tmp = malloc(number * size);
    
    if (tmp == NULL)
        return 0;
    
    memset(tmp, 0, number * size);
    return tmp;
}

#include <stdio.h>
#include <stdlib.h>


int main() {
    int n = 0;
    int d = 0;
    char c = 0;
    int result = 0;

    scanf("%d %d %c", &n, &d, &c);
    
    switch (c) {
        case '*' :
            result = n * d;
        break;
        
        case '+' :
            result = n + d;
        break;
        case '-' :
            result = n - d;
        break;
        case '/' :
            result = n / d;
        break;
        case '%' :
            result = n % d;
        break;
        default:
            printf("Usage error");
        break;
    }
    printf("%d", result);
    
    return 0;
}

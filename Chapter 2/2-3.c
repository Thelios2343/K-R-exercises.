#include <stdio.h>

int htoi(const char s[]);

int main(void)
{
    char hex[100];

    printf("Ingrese un numero hexadecimal: ");
    scanf("%99s", hex);   

    printf("Decimal: %d\n", htoi(hex));

    return 0;
}

int htoi(const char s[])
{
    int i = 0, n = 0, digit;

    if (s[i] == '0' && (s[i+1] == 'x' || s[i+1] == 'X'))
        i += 2;

    for (; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9')
            digit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            digit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            digit = s[i] - 'A' + 10;
        else
            break;

        n = n * 16 + digit;
    }

    return n;
}


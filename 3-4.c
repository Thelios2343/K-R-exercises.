#include <stdio.h>
#include <stdlib.h>

void itoa(int n, char s[]);
void my_reverse(char *s);

int main(void)
{
    int n = -154;
    char s[200];

    itoa(n, s);

    printf("el numero en string se ve asi: %s\n", s);

    return 0;
}

void itoa(int n, char s[])
{
    int i = 0;
    int sign = n;

    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';

    my_reverse(s);
}

void my_reverse(char *s)
{
    char *end = s;
    char temp;

    while (*end != '\0')
        end++;

    end--;

    while (s < end)
    {
        temp = *s;
        *s = *end;
        *end = temp;

        s++;
        end--;
    }
}

#include <stdio.h>

#define MAX_LEN 200

void itob (int n, char s[], int b);
void my_reverse (char *s);
int abs (int n);

int main () {

    int n = 255;
	char s[MAX_LEN];
    int b = 36;
	itob(n, s, b);

    if (b == 16) {
	printf("Decimal: %d, Conversion: 0x%s\n", n, s);
    } else {
    printf("Decimal: %d, Conversion: %s\n", n, s);
    }

    return 0;

}

void itob (int n, char s[], int b)
{
	int i;
	int sign = n;

	i = 0;

	do {
		char c;
		int m = abs(n % b);

		if (m < 10)
			c = m + '0';
		else 
			c = m - 10 + 'A';
		s[i++] = c;
	} while (n /= b);

	if (sign < 0){ 
		s[i++] = '-';
    }

	s[i] = '\0';
    my_reverse(s);
}

int abs (int n) {
    if (n < 0) {
        return -n;
    } else {
        return n;
    }
}

void my_reverse (char *s) {
    
    char *end = s;
    char temp;

    while ( *end != '\0') {
        end++;
    }
    
    end--;

    while (s < end) {
        
        temp = *s;
        *s = *end;
        *end = temp;

        s++;
        end --;
    }
}

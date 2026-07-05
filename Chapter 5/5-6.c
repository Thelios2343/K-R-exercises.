#include <stdio.h>

#define MAXVAL 1000

void get_line(char *s, int lim);
int atoi(char *s);
void itoa(int src, char *dest);
void reverse(char *s);
int strindex(char *s, char *t);
int abs(int n);

int main () {
    char s[MAXVAL];
    char a[16] = "-19293";
    int n = -542;
    char sgr[16];
    char asv[16] = "Angelsegura";
    char litio[16] = "segura";
    
    itoa(n, sgr);
    printf("Escribe un string: ");
    get_line(s, MAXVAL);
    printf("\nTu string fue: %s", s);
    printf("\nTu ascii a entero es: %d",atoi(a));
    printf("\nTu entero a ascii es: %s", sgr);
    printf("\nEn la cadena: %s. está la cadena: %s. inciando en la posicion: %d del arreglo\n", asv, litio, strindex(asv, litio));

    return 0;
}


void itoa (int src, char *s) { 
    char *t = s; 
    int sign = src;

    do {
        *s = abs(src % 10) + '0';
        s++;
    } while ((src /= 10) != 0);

    if (sign < 0) {
        *s = '-';
        s++;
    }

    *s = '\0';

    reverse(t);
}

void reverse(char *s) {
    char *end = s;
    char temp;

    while (*end != '\0') {
        end++;
    }

    end--;

    while (s < end) {
        temp =*s;
        *s = *end;
        *end = temp;

        s++;
        end--;
    }
}

int atoi(char *s) {
    int n = 0;
    int sign = 1;

    if (*s == '-') {
        sign = -1;
        s++;
    }
    else if (*s == '+') {
        s++;
    }

    for (; *s >= '0' && *s <= '9'; s++) {
        n = n * 10 + (*s - '0');
    }

    return n * sign;
}


void get_line(char *s, int lim) {
    int i = 0;
    int c = 0;
    while(c != '\n') {

        c = getchar();

        if (c == '\n' || c == '\t') {
            *s = '\0';
            return;
        }

        if (c == EOF) {
            *s = '\0';
            return;
        }

        if (i >= lim -1) {
            *s = '\0';
            return ;
        }
        *s = c;
        s++;
        i++;
    }
    *s = '\0';

    return;
}

int abs (int n) {
    if (n < 0) {
        return -n;
    }
    else {
        return n;
    }
}

int strindex(char *s, char *t) {
    char *p, *q, *start;
    
    for (start = s; *s != '\0'; s++) {
        for (p = s, q = t; *q != '\0' && *p == *q; p++, q++)
            ;
        if (*q == '\0')
            return s - start;  
    }
    return -1;
}


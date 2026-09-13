#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

void minprintf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    unsigned int uival;
    void *vval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd' :
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f' : 
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's' :
                for (sval = va_arg(ap, char *); *sval; sval ++) {
                    putchar(*sval);
                }
                break;
            case 'o':
                ival = va_arg(ap, unsigned int);
                printf("%o", ival);
                break;
            case 'c': 
                uival = va_arg(ap, int);
                printf("%c", uival);
                break;
            case 'u':
                uival = va_arg(ap, unsigned int);
                printf("%u", uival);
                break;
            case 'x': 
                uival = va_arg(ap, unsigned int);
                printf("%x", uival);
                break;
            case 'p': 
                vval = va_arg(ap, void *);
                printf("%p", vval);
                break;
            case '%':
                putchar('%');
                break;
            default:
                putchar(*p);
                break;
            }
    }
    va_end(ap);
}
int main () {
    int c = 0x43;
    int *p = &c;

    minprintf("%d\n", *p);
    minprintf("Holaaaa%c\n", *p);
    minprintf("%p\n", p);
    return 0;
}

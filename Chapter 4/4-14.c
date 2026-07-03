#include <stdio.h>

#define swap(t, x, y) do { \
    t _temp = (x);          \
    (x) = (y);              \
    (y) = _temp;            \
} while (0)

int main() {
    int a = 5, b = 10;
    printf("Antes: a = %d, b = %d\n", a, b);
    swap(int, a, b);
    printf("Después: a = %d, b = %d\n", a, b);

    double c = 1.2, d = 3.4;
    printf("Antes: c = %.1f, d = %.1f\n", c, d);
    swap(double, c, d);
    printf("Después: c = %.1f, d = %.1f\n", c, d);

    return 0;
}

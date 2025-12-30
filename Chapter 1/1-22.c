#include <stdio.h>

#define LIMIT 10

int main(void)
{
    int c;
    char buf[LIMIT];
    int len = 0;
    int last_blank = -1;
    int i;

    while ((c = getchar()) != EOF) {

        if (c == '\n') {
            for (i = 0; i < len; ++i)
                putchar(buf[i]);
            putchar('\n');
            len = 0;
            last_blank = -1;
            continue;
        }

        buf[len++] = c;

        if (c == ' ' || c == '\t')
            last_blank = len - 1;

        if (len == LIMIT) {

            if (last_blank != -1) {
                
                for (i = 0; i < last_blank; ++i)
                    putchar(buf[i]);
                putchar('\n');

                
                len = len - last_blank - 1;
                for (i = 0; i < len; i++)
                    buf[i] = buf[last_blank + 1 + i];
            } else {
                
                for (i = 0; i < len; ++i)
                    putchar(buf[i]);
                putchar('\n');
                len = 0;
            }

            last_blank = -1;
        }
    }

    
    for (i = 0; i < len; ++i)
        putchar(buf[i]);

    return 0;
}


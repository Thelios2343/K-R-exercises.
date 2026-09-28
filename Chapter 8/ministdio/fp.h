#include <unistd.h>
#include <stdlib.h>

#define OPEN_MAX 20
#define BUFSIZ 1024
#define EOF (-1) 


typedef struct _iobuf {
    char *ptr;
    int cnt;
    char *base;
    unsigned read:1;
    unsigned write:1;
    unsigned unbuf:1;
    unsigned eof:1;
    unsigned err:1;
    int fd;
} FILE;

extern FILE _iob[OPEN_MAX];

enum _flags { MODE_READ, MODE_WRITE, MODE_READ_WRITE };

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) ((p)->eof != 0)
#define ferror(p) ((p)->err != 0)
#define fileno(p) ((p) -> fd)

#define getc(p) ((p) -> cnt-- > 0\
        ? (unsigned char) *(p)->ptr++\
        : _fillbuf(p))

#define putc(x, p) \
    (--(p)->cnt >= 0 \
    ? *(p)->ptr++ = (x) \
     : _flushbuf((x), (p)))


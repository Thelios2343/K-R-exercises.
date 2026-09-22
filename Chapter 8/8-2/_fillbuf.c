#include "fp.h"

int _fillbuf(FILE *fp) {
    int bufsize;

    if (!fp->read || fp->eof || fp->err)
        return EOF;

    while ((fp->base == NULL) && bufsize == 0)
        bufsize = fp->unbuf ? 1 : BUFSIZ;

    if (fp->base == NULL) {
        bufsize = fp->unbuf ? 1 : BUFSIZ;
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (fp->cnt <= 0) {
        if (fp->cnt == 0)
            fp->eof = 1;
        else
            fp->err = 1;
        return EOF;
    }

    fp->cnt--;
    return (unsigned char) *fp->ptr++;
}

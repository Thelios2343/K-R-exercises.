#include <fcntl.h>
#include "fp.h"

FILE *f_open(char *name, char *mode);
int __flushbuf(FILE *f);
int _fillbuf(FILE *p);
int fflush(FILE *f);
int fputc(int c, FILE *f);
int fclose(FILE *f);
off_t fseek(FILE *fp, long offset, int origin);

FILE _iob[OPEN_MAX] = {
    { NULL, 0, NULL, 1, 0, 0, 0, 0, 0 },  /* input  */
    { NULL, 0, NULL, 0, 1, 0, 0, 0, 1 },  /* output */
    { NULL, 0, NULL, 0, 1, 1, 0, 0, 2 },  /* error */
};

FILE *f_open(char *name, char *mode) {

    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') 
        return NULL;
    
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp -> read == 0 && fp -> write == 0)
            break;
    if (fp >= _iob + OPEN_MAX) 
        return NULL;

    if (*mode == 'w')
        fd = creat(name, 0666);
    else if (*mode == 'a') {
        if ((fd = open(name, MODE_READ_WRITE, 0)) == -1)
            fd = creat(name, 0666);
        lseek(fd, 0L, 2);
    } else 
        fd = open(name, MODE_READ, 0);

    if (fd == -1) 
        return NULL;

    fp -> fd = fd;
    fp -> cnt = 0;
    fp -> base = NULL;
    fp -> eof = 0;
    fp -> err = 0;

    if (*mode == 'r') {
        fp -> read = 1;
        fp -> write = 0;
    } else {
        fp -> read = 0;
        fp -> write = 1;
    }

    return fp;
}

int _fillbuf(FILE *fp) {
    int bufsize;

    if (!fp -> read || fp -> eof || fp -> err)
        return EOF;

    while ((fp -> base == NULL) && bufsize == 0)
        bufsize = fp -> unbuf ? 1 : BUFSIZ;

    if (fp -> base == NULL) {
        bufsize = fp -> unbuf ? 1 : BUFSIZ;
        if ((fp -> base = malloc(bufsize)) == NULL)
            return EOF;
    }

    fp -> ptr = fp -> base;
    fp -> cnt = read(fp -> fd, fp -> ptr, bufsize);

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

int _flushbuf(int c, FILE *fp) {
    int n = fp -> ptr - fp -> base;

    if (fp -> base == NULL) 
        fp -> base = malloc(BUFSIZ);

    if (n > 0)
        write(fp -> fd, fp -> base, n);

    fp -> ptr = fp->base;
    fp -> cnt = BUFSIZ;

    *fp -> ptr++ = c;
    fp -> cnt--;

    return c;
}

int fflush(FILE *fp) {
    if (!fp) 
        return EOF;
    else { 
        write(fp -> fd, fp->base, fp -> ptr - fp -> base);
        fp -> ptr = fp -> base;
        fp -> cnt = BUFSIZ;
    }
    return 0;
}

int fclose(FILE *fp) {
    int result;

    if (!fp) 
        return EOF;
    
    result = fflush(fp);
    
    if (close(fp -> fd) < 0)
        result = EOF;

    free(fp -> base);
    free(fp);

    return result;
}

off_t fseek(FILE *fp, long offset, int origin) {
    if (fp -> read) {
        if(fflush(fp) == EOF)
            return EOF;
    }

    if (lseek(fp -> fd, offset, origin) == (off_t)-1) 
        return EOF;
    
    fp -> ptr = fp -> base;
    fp -> cnt = 0;

    return 0;
}

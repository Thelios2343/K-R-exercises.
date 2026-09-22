#include <fcntl.h>
#include "fp.h"
#include <unistd.h>

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
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, 0666);
        lseek(fd, 0L, 2);
    } else 
        fd = open(name, O_RDONLY, 0);

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

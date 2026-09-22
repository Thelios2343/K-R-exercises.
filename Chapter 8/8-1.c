#include <fcntl.h>
#include <unistd.h>

#define MAXBUFFER 8192

int main(int argc, char *argv[]) {
    int fd;
    ssize_t n;
    char buf[MAXBUFFER];
    
    if (argc < 2 || argc >= 3) {
        write(STDOUT_FILENO, "Error No specified file\n", 25);
        return 0;
    }

    fd = open(argv[1], O_RDONLY);
    
    while((n = read(fd, buf, MAXBUFFER)) > 0)
        write(STDOUT_FILENO, buf, n);

    close(fd);
    return 0;
}

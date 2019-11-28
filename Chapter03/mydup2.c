#include <fcntl.h>

#include "apue.h"

int my_dup2(int fd, int fd2) {
    if (fd2 > open_max()) {
        return -1;
    }

    /*
     * use lseek to verify whether fd is valid
     */
    if (lseek(fd, 0, SEEK_CUR) < 0 && errno == EBADF) {
        printf("file descriptor: %d is not valid, %m\n", fd);
        return -1;
    }

    /* return if fd2 is fd */
    if (fd == fd2) {
        return fd2;
    }

    close(fd2);

    long i = 0;
    for (i = 0; i < open_max(); i++) {
        i = dup(fd);
        if (i == fd2) {
            break;
        }
    }
    /* for (; i > fd; i--) { */
    /*   close(i); */
    /* } */

    return (fd2);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        err_sys("usage: ./a.out <string>");
    }
    printf("%ld\n", open_max());
    my_dup2(STDERR_FILENO, 5);
    for (long i = 1; i < argc; ++i) {
        write(5, argv[i], strlen(argv[i]));
        write(5, "\n", 1);
    }

    close(5);
    return 0;
}

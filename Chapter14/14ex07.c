/**
 *   @file     14ex07.c
 *   @date     2019-12-29
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    pipe using nonblocking writes.
 */

#include <fcntl.h>
#include <limits.h>

#include "apue.h"

int main(void) {
    int fd[2];

    if (pipe(fd) < 0) {
        err_sys("pipe error.");
    }

    set_fl(fd[1], O_NONBLOCK);

    int capacity;
    for (capacity = 0;; capacity++) {
        int nwritten = 0;
        if ((nwritten = write(fd[1], "a", 1)) != 1) {
            printf("nwritten = %d\n", nwritten);
            break;
        }
    }

    printf("capacity = %d\n", capacity);

    printf("PIPE_BUF = %d\n", PIPE_BUF);

    exit(EXIT_SUCCESS);

}

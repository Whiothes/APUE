/**
 *   @file     14fig01.c
 *   @date     2019-12-15
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Figure 14.1 Large nonblocking write
 */
#include <errno.h>
#include <fcntl.h>

#include "apue.h"

char buf[50000];

int main(void) {
    int   ntowrite, nwrite;
    char *ptr;

    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);

    set_fl(STDOUT_FILENO, O_NONBLOCK);

    ptr = buf;
    while (ntowrite > 0) {
        errno  = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

        if (nwrite > 0) {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }

    clr_fl(STDOUT_FILENO, O_NONBLOCK);

    exit(EXIT_SUCCESS);
}

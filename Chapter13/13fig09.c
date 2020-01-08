/**
 *   @file     13fig09.c
 *   @date     2019-12-01
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    solve multiple file descriptors may left open
 */

#include <fcntl.h>

#include "apue.h"

int set_cloexec(int fd) {
    int val;

    if ((val = fcntl(fd, FD_GETFD, 0)) < 0) {
        return (-1);
    }

    val |= FD_CLOEXEC;
    return (fcntl(fd, FD_SETFD, val));
}

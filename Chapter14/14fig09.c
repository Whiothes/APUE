/**
 *   @file     14fig09.c
 *   @date     2019-12-16
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Place a write lock on an entire file
 */

#include <fcntl.h>

#include "apue.h"

int lockfile(int fd) {
    struct flock fl;

    fl.l_type   = F_WRLCK;
    fl.l_start  = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len    = 0;

    return (fcntl(fd, F_SETLK, &fl));
}

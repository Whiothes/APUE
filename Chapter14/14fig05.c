/**
 *   @file     14fig05.c
 *   @date     2019-12-16
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Function to lock or unlock a region of a file
 */

#include <fcntl.h>

#include "apue.h"

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len) {
    struct flock lock;

    lock.l_type   = type;
    lock.l_start  = offset;
    lock.l_whence = whence;
    lock.l_len    = len;

    return (fcntl(fd, cmd, &lock));
}

/**
 *   @file     14fig06.c
 *   @date     2019-12-16
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Figure 14.6 Function to test for a locking condition
 */
#include <fcntl.h>

#include "apue.h"

pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len) {
    struct flock lock;

    lock.l_type   = type;
    lock.l_start  = offset;
    lock.l_whence = whence;
    lock.l_len    = len;

    if (fcntl(fd, F_GETLK, &lock) < 0) {
        err_sys("fcntl error");
    }

    if (lock.l_type == F_UNLCK) {
        return 0;
    }

    return (lock.l_pid);
}

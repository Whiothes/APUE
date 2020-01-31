/**
 *   @file     16ex06.c
 *   @date     2020-01-31
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    routines to set/unset socket asynchronous
 *
 *  Detailed description
 *
 */

#include "apue.h"
#include <fcntl.h>

int setasync(int sockfd) {
    int n;

    if (fcntl(sockfd, F_SETOWN, getpid()) < 0) {
        return -1;
    }

    n = 1;
    if (ioctl(sockfd, FIOASYNC, &n) < 0) {
        return -1;
    }

    return 0;
}

int unsetasync(int sockfd) {
    int n = 0;
    if (ioctl(sockfd, FIOASYNC, &n) < 0) {
        return -1;
    }
    return 0;
}

/**
 *   @file     14fig24.c
 *   @date     2019-12-28
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    implementations of readn and writen
 */

#include <fcntl.h>

#include "apue.h"

ssize_t readn(int fd, void *ptr, size_t n) {
    size_t  nleft;
    ssize_t nread;

    for (nleft = n; nleft > 0; nleft -= nread) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            // error occured
            if (nleft == n) {
                // no read
                return -1;
            } else {
                // return read amount
                break;
            }
        } else if (nread == 0) {
            break;
        }
        ptr += nread;
    }

    return n - nleft;
}

ssize_t writen(int fd, const void *ptr, size_t n) {
    size_t  nleft;
    ssize_t nwritten;

    for (nleft = n; nleft > 0; nleft -= nwritten) {
        if ((nwritten = write(fd, ptr, nleft) < 0)) {
            // error occured
            if (nleft == n) {
                // no written
                return -1;
            } else {
                // return written amount
                break;
            }
        } else if (nwritten == 0) {
            break;
        }
        ptr += nwritten;
    }

    return n - nleft;
}

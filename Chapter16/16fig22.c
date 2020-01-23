/**
 *   @file     16fig22.c
 *   @date     2020-01-23
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    initialize a socket endpoint for use by a server
 *              with address reuse
 */

#include <errno.h>
#include <sys/socket.h>

#include "apue.h"

int initserver(int type, const struct sockaddr *addr, socklen_t alen,
               int qlen) {
    int fd, err;
    int reuse;

    if ((fd = socket(addr->sa_family, type, 0)) < 0) {
        return -1;
    }

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0) {
        goto errout;
    }

    if (bind(fd, addr, alen) < 0) {
        goto errout;
    }

    if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if (listen(fd, qlen) < 0) {
            goto errout;
        }
    }

    return fd;

errout:
    err = errno;
    close(fd);
    errno = err;
    return -1;
}

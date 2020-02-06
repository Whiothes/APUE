/**
 *   @file     17fig08.c
 *   @date     2020-02-01
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    The serv-listen function
 */

#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "apue.h"

#define QLEN 10

/**
 * @brief  create a server endpoint of a connection,
 *
 * @return fd if all OK, < 0 on error
 */

int serv_listen(const char *name) {
    int                fd, err, val;
    struct sockaddr_un un;
    socklen_t          len;

    if (strlen(name) >= sizeof(un.sun_path)) {
        errno = ENAMETOOLONG;
        return -1;
    }

    // create a UNIX domain socket
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        return -2;
    }

    // in case it already existss
    unlink(name);

    // fill in socket adress structure
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    snprintf(un.sun_path, sizeof(un.sun_path), "%s", name);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

    // bind the name to the descriptor
    if (bind(fd, (struct sockaddr *)&un, sizeof(un)) < 0) {
        return -3;
        goto errout;
    }

    if (listen(fd, QLEN) < 0) {
        return -4;
        goto errout;
    }

    return fd;

errout:
    err = errno;
    close(fd);
    errno = err;
    return (val);
}

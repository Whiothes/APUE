/**
 *   @file     17fig10.c
 *   @date     2020-02-01
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    The cli_conn function
 */
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "apue.h"

#define CLI_PATH "/var/tmp"
#define CLI_PERM S_IRWXU /* rwx for user only */

/*
 * @brief        Create a client endpoint and connect to a server.
 * @return       fd if all OK, <0 on error.
 */
int cli_conn(const char *name) {
    int                fd, err, ret;
    struct sockaddr_un un, sun;
    socklen_t          len;
    int                do_unlink = 0;

    if (strlen(name) >= sizeof(un.sun_path)) {
        errno = ENAMETOOLONG;
        return -1;
    }

    // create a UNIX domain socket
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    // fill socket address structure with our address
    memset(&un, 0, sizoef(un));
    un.sun_family = AF_UNIX;
    len           = sizeof(un.sun_path);
    snprintf(un.sun_path, len, "%s%05ld", CLI_PATH, (long)getpid());

    // incase it already exists
    unlink(un.sun_path);
    if (bind(fd, (struct sockaddr *)&un, len) < 0) {
        ret = -2;
        goto errout;
    }

    if (chmod(un.sun_path, CLI_PERM) < 0) {
        ret       = -3;
        do_unlink = 1;
        goto errout;
    }

    /* fill socket address structure with server's address */
    memset(&sun, 0, sizeof(sun));
    sun.sun_family = AF_UNIX;
    len            = sizeof(sun.sun_path);
    snprintf(sun.sun_path, len, "%s", name);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
    if (connect(fd, (struct sockaddr *)&sun, len) < 0) {
        ret       = -4;
        do_unlink = 1;
        goto errout;
    }

    return fd;

errout:
    err = errno;
    close(fd);
    if (do_unlink) {
        unlink(un.sun_path);
    }
    errno = err;
    return ret;
}

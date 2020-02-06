/**
 *   @file     17fig09.c
 *   @date     2020-02-01
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    The serv_accept function
 */

#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>

#include "apue.h"

// client's name can't be older than this (sec)
#define STALE 30

/**
 *  @brief wait for client connection to arrive and accept it
 *
 *  We also obtain the client's user ID from the pathname
 *  that it must bind before calling us.
 *
 *  @return new fd if all OK, <0 on error
 */
int serv_accept(int listenfd, uid_t *uidptr) {
    char *             name;
    int                c, err, ret;
    time_t             staletime;
    struct sockaddr_un un;
    struct stat        statbuf;
    socklen_t          len;

    // allocate enough space for longest name plus terminating null
    if ((name = malloc(sizeof(un.sun_path) + 1)) == NULL) {
        return -1;
    }

    len = sizeof(un);
    if ((c = accept(listenfd, (struct sockaddr *)&un, &len)) < 0) {
        free(name);
        return -2;
    }

    // obtain the client's uid from its calling address
    len -= offsetof(struct sockaddr_un, sun_path);
    memcpy(name, un.sun_path, len);
    name[len] = 0;
    if (stat(name, &statbuf) < 0) {
        ret = -3;
        goto errout;
    }

#ifdef S_ISSOCK

    if (S_ISSOCK(statbuf.st_mode) == 0) {
        // not a socket
        ret = -4;
        goto errout;
    }

#endif  // S_ISSOCK

    staletime = time(NULL) - STALE;
    if ((statbuf.st_mode & (S_IRWXG | S_IRWXO)) ||
#if defined(__APPLE__)
        (statbuf.st_atimespec.tv_sec < staletime) ||
        (statbuf.st_ctimespec.tv_sec < staletime) ||
        (statbuf.st_mtimespec.tv_sec < staletime)) {
#elif defined(__linux__)
        (statbuf.st_atime < staletime) || (statbuf.st_ctime < staletime) ||
        (statbuf.st_mtime < staletime)) {
#endif
        // i-node is too old
        ret = -6;
        goto errout;
    }

    if (uidptr != NULL) {
        *uidptr = statbuf.st_uid;
    }

    unlink(name);
    free(name);
    return c;

errout:
    err = errno;
    close(c);
    free(name);
    errno = err;
    return ret;
}

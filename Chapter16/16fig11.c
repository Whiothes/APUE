/**
 *   @file     16fig11.c
 *   @date     2020-01-22
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    portable connect with retry
 */

#include <sys/socket.h>

#include "apue.h"

#define MAXSLEEP 128

int connect_retry(int domain, int type, int protocol,
                  const struct sockaddr *addr, socklen_t alen) {
    int numsec, fd;

    // Try to connect with expotential backoff.
    for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1) {
        if ((fd = socket(domain, type, protocol)) < 0) {
            return -1;
        }

        if (connect(fd, addr, alen) == 0) {
            // connection accepted
            return fd;
        }
        close(fd);

        // delay before trying again.
        if (numsec <= MAXSLEEP / 2) {
            sleep(numsec);
        }
    }

    return -1;
}

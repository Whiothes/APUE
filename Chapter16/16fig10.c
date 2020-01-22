/**
 *   @file     16fig10.c
 *   @date     2020-01-22
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    connect with retry
 */
#include <sys/socket.h>

#include "apue.h"
#define MAXSLEEP 128

int connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen) {
    int numsec;

    // Try to connect with exponential backoff.
    for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1) {
        if (connect(sockfd, addr, alen) == 0) {
            return 0;
        }

        if (numsec <= MAXSLEEP / 2) {
            sleep(numsec);
        }
    }

    return -1;
}

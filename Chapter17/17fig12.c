/**
 *   @file     17fig12.c
 *   @date     2020-02-02
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    The send_err function
 */

#include "apue.h"

/*
 * Used when we had planned to send an fd using send_fd(),
 * but encountered an error instead. We send the error back
 * using the send_fd()/recv_fd() protocol.
 */
int send_err(int fd, int errcode, const char *msg) {
    int n;

    if ((n = strlen(msg)) > 0) {
        if (write(fd, msg, strlen(msg)) != n) {
            /* send the error message */
            return -1;
        }
    }

    if (errcode >= 0) {
        /* must be negative */
        errcode = -1;
    }

    if (send_fd(fd, errcode) < 0) {
        return -1;
    }

    return (0);
}

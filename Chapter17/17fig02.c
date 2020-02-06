/**
 *   @file     17fig02.c
 *   @date     2020-01-31
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    create a full-duplex pipe by socketpair
 */

#include <sys/socket.h>

#include "apue.h"

/**
 *  @brief returns a full-duplex pipe (a UNIX domain socket)
 *
 *  with the two file descriptors returned in fd[0] and fd[1].
 */
int fd_pipe(int fd[2]) { return (socketpair(AF_UNIX, SOCK_STREAM, 0, fd)); }

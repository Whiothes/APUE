/**
 *   @file     17fig05.c
 *   @date     2020-02-01
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Binding an address to a UNIX domain socket
 */

#include <sys/socket.h>
#include <sys/un.h>

#include "apue.h"

int main(void) {
    int                fd, size;
    struct sockaddr_un un;

    un.sun_family = AF_UNIX;
    snprintf(un.sun_path, sizeof(un.sun_path), "%s", "foo.socket");

    if ((fd = socket(un.sun_family, SOCK_STREAM, 0)) < 0) {
        err_sys("socket error");
    }

    size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

    if (bind(fd, (struct sockaddr *)&un, size) < 0) {
        err_sys("bind error");
    }

    printf("UNIX domain socket bound\n");
    exit(EXIT_SUCCESS);
}

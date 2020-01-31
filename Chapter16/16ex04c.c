/**
 *   @file     16ex04c.c
 *   @date     2020-01-31
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    client program for returning processes number
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>

#include "apue.h"

extern char *__progname;

int requests(struct addrinfo *aip) {
    int  c;
    char buf[BUFSIZ];

    c = socket(aip->ai_family, aip->ai_socktype, 0);
    if (c < 0) {
        err_quit("socket error");
    }

    if (connect(c, aip->ai_addr, aip->ai_addrlen) < 0) {
        err_quit("connect error");
    }

    recv(c, buf, sizeof(buf), 0);

    printf("recv: %s\n", buf);

    return 0;
}

int print_addrinfo(struct addrinfo *aip) {
    char                 abuf[INET_ADDRSTRLEN], abuf6[INET6_ADDRSTRLEN];
    struct sockaddr_in  *sinp;
    struct sockaddr_in6 *sinp6;
    const char          *addr;
    short                port;

    if (aip->ai_family == AF_INET) {
        sinp = (struct sockaddr_in *)aip->ai_addr;
        addr = inet_ntop(aip->ai_family, &sinp->sin_addr, abuf, aip->ai_addrlen);
        port = ntohs(sinp->sin_port);
    } else if (aip->ai_family == AF_INET6) {
        sinp6 = (struct sockaddr_in6 *)aip->ai_addr;
        addr  = inet_ntop(aip->ai_family, &sinp6->sin6_addr, abuf, aip->ai_addrlen);
        port  = ntohs(sinp6->sin6_port);
    }
    printf("address: %s\n", addr);
    printf("port: %d\n", port);

    return 0;
}

int main(int argc, char *argv[]) {
    struct addrinfo *aip, *ailist;
    struct addrinfo  hint;
    int              c, err;

    if (argc < 2) {
        err_msg("usage: %s host port", __progname);
    }

    memset(&hint, 0, sizeof(hint));
    hint.ai_flags    = AI_ALL;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_addr     = NULL;
    hint.ai_next     = NULL;

    if ((err = getaddrinfo(argv[1], argv[2], &hint, &ailist)) < 0) {
        err_quit("getaddrinfo: %s", gai_strerror(err));
    }

    for (aip = ailist; aip; aip = aip->ai_next) {
        print_addrinfo(aip);
        requests(aip);
    }
}

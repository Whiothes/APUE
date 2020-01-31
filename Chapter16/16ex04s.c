/**
 *   @file     16ex04s.c
 *   @date     2020-01-30
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    server program for returning processes number
 */

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "apue.h"

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

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
        sinp6 = (struct sockaddr_in6*)aip->ai_addr;
        addr  = inet_ntop(aip->ai_family, &sinp6->sin6_addr, abuf, aip->ai_addrlen);
        port  = ntohs(sinp6->sin6_port);
    }
    log_msg("address: %s", addr);
    log_msg("port: %d", port);
}

int serve(struct addrinfo *aip) {
    int   s, c;
    char  buf[BUFSIZ];
    FILE *fp;

    socket(aip->ai_family, aip->ai_socktype, 0);

    s = socket(aip->ai_family, aip->ai_socktype, 0);
    if (s < 0) {
        log_sys("socket error");
    }

    if (bind(s, aip->ai_addr, aip->ai_addrlen) < 0) {
        log_sys("bind error");
    }

    if (listen(s, 10) < 0) {
        log_sys("listen error");
    }

    for (;;) {
        c = accept(s, NULL, NULL);
        if (c < 0) {
            log_sys("accept error");
        }

        if (fcntl(c, F_SETFD, fcntl(c, F_GETFD, 0) | FD_CLOEXEC) < 0) {
            log_sys("fcntl error");
        }

        if ((fp = popen("ps -ef | wc -l ", "r")) == NULL) {
            snprintf(buf, sizeof(buf), "%s", strerror(errno));
            err_msg(buf);
        } else {
            fgets(buf, sizeof(buf), fp);
            send(c, buf, strlen(buf), 0);
        }

        pclose(fp);
        close(c);
    }
}

int main() {
    struct addrinfo     *ailist, *aip;
    struct addrinfo      hint;
    char                *host;
    int                  err;
    size_t               n;

    if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0) {
        n = HOST_NAME_MAX;
    }

    if ((host = (char *)malloc(n)) == NULL) {
        err_sys("malloc error");
    }

    if (gethostname(host, n) < 0) {
        err_sys("gethostname error");
    }

    daemonize("PS Number");

    log_msg("service started");

    memset(&hint, 0, sizeof(hint));
    hint.ai_flags     = AI_CANONNAME;
    hint.ai_socktype  = SOCK_STREAM;
    hint.ai_addr      = NULL;
    hint.ai_canonname = NULL;
    hint.ai_next      = NULL;

    if ((err = getaddrinfo(host, "4000", &hint, &ailist)) < 0) {
        log_sys("getaddrinfo error");
    }

    for (aip = ailist; aip; aip = aip->ai_next) {
        if (fork() == 0) {
            print_addrinfo(aip);
            serve(aip);
        }
    }
}

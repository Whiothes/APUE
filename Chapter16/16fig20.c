/**
 *   @file     16fig20.c
 *   @date     2020-01-22
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    erver providing system uptime over datagrams.
 */

#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <syslog.h>

#include "apue.h"

#define BUFLEN     128
#define MAXADDRLEN 256

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif  // HOST_NAME_MAX

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void serve(int sockfd) {
    int              n;
    socklen_t        alen;
    FILE *           fp;
    char             buf[BUFLEN];
    char             abuf[MAXADDRLEN];
    struct sockaddr *addr = (struct sockaddr *)abuf;

    set_cloexec(sockfd);
    for (;;) {
        alen = MAXADDRLEN;
        if ((n = recvfrom(sockfd, buf, BUFLEN, 0, addr, &alen)) < 0) {
            syslog(LOG_ERR, "ruptimed: recvfrom error: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {
            strerror_r(errno, buf, sizeof(buf));
            sendto(sockfd, buf, strlen(buf), 0, addr, alen);
        } else {
            if (fgets(buf, BUFLEN, fp) != NULL) {
                sendto(sockfd, buf, strlen(buf), 0, addr, alen);
            }
            pclose(fp);
        }
    }
}

int main(int argc, char *argv[]) {
    struct addrinfo *ailist, *aip;
    struct addrinfo  hint;
    int              sockfd, err, n;
    char *           host;

    if (argc != 1) {
        err_quit("usage: ruptimed");
    }

    if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0) {
        n = HOST_NAME_MAX;
    }

    if ((host = malloc(n)) == NULL) {
        err_sys("malloc error");
    }
    if (gethostname(host, n) < 0) {
        err_sys("gethostname error");
    }

    daemonize("ruptimed");

    memset(&hint, 0, sizeof(hint));
    hint.ai_flags     = AI_CANONNAME;
    hint.ai_socktype  = SOCK_DGRAM;
    hint.ai_addr      = NULL;
    hint.ai_canonname = NULL;
    hint.ai_next      = NULL;

    if ((err = getaddrinfo(host, "4001", &hint, &ailist)) < 0) {
        syslog(LOG_ERR, "getaddrinfo error: %s", gai_strerror(err));
        exit(EXIT_FAILURE);
    }

    for (aip = ailist; aip; aip = aip->ai_next) {
        if ((sockfd = initserver(SOCK_DGRAM, aip->ai_addr,
                                 aip->ai_addrlen, 0)) >= 0) {
            serve(sockfd);
            exit(EXIT_SUCCESS);
        }
    }

    exit(EXIT_FAILURE);
}

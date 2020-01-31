/**
 *   @file     16ex03.c
 *   @date     2020-01-27
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    amend 16fig17.c for multiple services
 */

#include <errno.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <syslog.h>

#include "apue.h"

#define BUFLEN 128
#define QLEN   10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif /* HOST_NAME_MAX */

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void serve(int sockfd) {
    int   clfd;
    FILE *fp;
    char  buf[BUFLEN];

    set_cloexec(sockfd);
    for (;;) {
        if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
            syslog(LOG_ERR, "ruptimed: accept error: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        set_cloexec(clfd);

        if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {
            sprintf(buf, "error: %s\n", strerror(errno));
            send(clfd, buf, strlen(buf), 0);
        } else {
            while (fgets(buf, BUFLEN, fp) != NULL) {
                send(clfd, buf, strlen(buf), 0);
            }
            pclose(fp);
        }
        close(clfd);
    }
}

int main(int argc, char *argv[]) {
    struct addrinfo *ailist, *aip;
    struct addrinfo  hint;
    int              sockfd, err, n;
    char *           host;
    fd_set           allset;

    if (argc != 1) {
        err_quit("usage: ruptimed");
    }
    if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0) {
        n = HOST_NAME_MAX;
    }
    if ((host = (char *)malloc(n)) == NULL) {
        err_sys("malloc error");
    }
    if (gethostname(host, n) < 0) {
        err_sys("gethostname error");
    } else {
        printf("hostname: %s\n", host);
    }

    daemonize("ruptimed");

    memset(&hint, 0, sizeof(hint));
    hint.ai_flags     = AI_CANONNAME;
    hint.ai_socktype  = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr      = NULL;
    hint.ai_next      = NULL;
    if ((err = getaddrinfo(host, "4000", &hint, &ailist)) != 0) {
        syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s", gai_strerror(err));
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&allset);
    for (aip = ailist; aip; aip = aip->ai_next) {
        if (fork() == 0) {
            if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr, aip->ai_addrlen,
                                     QLEN)) >= 0) {
                serve(sockfd);
                exit(EXIT_SUCCESS);
            }
        }
    }

    exit(EXIT_SUCCESS);
}

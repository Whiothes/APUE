/**
 *   @file     16ex05.c
 *   @date     2020-01-22
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  2.0
 *   @brief    server program illustrating command wrting directly to socket
 *
 *   redesign for no-delay processing
 */

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <syslog.h>

#include "apue.h"

#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif  // HOST_NAME_MAX

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void serve(int sockfd) {
    int   clfd, status;
    pid_t pid;

    set_cloexec(sockfd);

    for (;;) {
        if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
            syslog(LOG_ERR, "ruptimed: accept error: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if ((pid = fork()) < 0) {
            syslog(LOG_ERR, "ruptimed: fork error: %s", strerror(errno));
            exit(EXIT_FAILURE);
        } else if (pid == 0) {  // child
            if (dup2(clfd, STDOUT_FILENO) != STDOUT_FILENO ||
                dup2(clfd, STDERR_FILENO) != STDERR_FILENO) {
                syslog(LOG_ERR, "ruptimed: unexpected error");
                exit(EXIT_FAILURE);
            }
            close(clfd);
            execl("/usr/bin/uptime", "uptime", (char *)0);
            syslog(LOG_ERR, "ruptimed: unexpected return from exec: %s",
                   strerror(errno));
        } else {
            close(clfd);
            waitpid(pid, &status, 0);
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
    hint.ai_socktype  = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr      = NULL;
    hint.ai_next      = NULL;
    if ((err = getaddrinfo(host, "4000", &hint, &ailist)) != 0) {
        syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s", gai_strerror(err));
        exit(EXIT_FAILURE);
    }

    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if (fork() == 0) {
            if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr, aip->ai_addrlen,
                                     QLEN)) >= 0) {
                serve(sockfd);
                exit(EXIT_SUCCESS);
            } else {
                close (sockfd);
            }
        }
    }
    exit(EXIT_FAILURE);
}

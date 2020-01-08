/**
 *   @file     10fig10.c
 *   @date     2019-10-26
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    calling read() with timeout
 *
 *  @bug race condition between first call to alarm() and read()
 *  @bug if system are automatically restarted, the read is not interrupted
 *
 */
#include <signal.h>

#include "apue.h"
static void sig_alrm(int);

int main(void) {
    int  n;
    char line[MAXLINE];

    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        err_sys("signal(SIGALRM) error");
    }

    alarm(10);
    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
        err_sys("read error");
    }

    alarm(0);

    write(STDOUT_FILENO, line, n);
    exit(0);
}

static void sig_alrm(int signo) {}

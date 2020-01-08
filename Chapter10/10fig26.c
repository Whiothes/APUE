/**
 *   @file     10fig26.c
 *   @date     2019-10-28
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Using system to invoke the ed editor
 */
#include "apue.h"

static void sig_int(int signo) { printf("caught SIGINT\n"); }

static void sig_chld(int signo) { printf("caught SIGCHLD\n"); }

int main(void) {
    if (signal(SIGINT, sig_int) == SIG_ERR) err_sys("signal(SIGINT) error");
    if (signal(SIGCHLD, sig_chld) == SIG_ERR) err_sys("signal(SIGCHLD) error");
    if (system("/bin/ed") < 0) err_sys("system() error");

    exit(0);
}

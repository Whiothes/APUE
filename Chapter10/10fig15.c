/**
 *   @file     10fig15.c
 *   @date     2019-10-27
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Example of signal sets and sigprocmask
 *
 *  shows many of the signal features that we’ve been describing.
 *
 */

#include "apue.h"

static void sig_quit(int);

int main(void) {
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
        err_sys("can't catch sigquit");
    }

    // Block SIGQUIT and save current sig mask.
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        err_sys("SIG_BLCOK error");
    }

    sleep(5);

    if (sigpending(&pendmask) < 0) {
        err_sys("sigpending error");
    }
    if (sigismember(&pendmask, SIGQUIT)) {
        printf("\nSIGQUIT pending\n");
    }

    // Restore signal mask which unblock SIGQUIT
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        err_sys("SIG_SETMASK error");
    }
    printf("SIGQUIT unblocked");

    sleep(5);
    exit(0);
}

static void sig_quit(int signo) {
    printf("caught SIGQUIT\n");

    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        err_sys("can't reset SIGQUIT");
    }
}

/**
 *   @file     10fig22.c
 *   @date     2019-10-28
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Protecting a critical region from a signal
 *   the correct way to protect a critical region of code from a speciﬁc signal.
 */

#include "apue.h"

static void sig_int(int);

int main(void) {
    sigset_t newmask, oldmask, waitmask;

    pr_mask("program start: ");

    if (signal(SIGINT, sig_int) == SIG_ERR) err_sys("signal(SIGINT) error");

    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    // block SIGINT and save current signal mask
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("SIG_BLOCK error");

    // critical region of code
    pr_mask("in critical region: ");
    // pause, allowing all signals except SIGUSR1
    if (sigsuspend(&waitmask) != -1) err_sys("sigsuspend error");

    pr_mask("after return from sigsuspend");

    // reset signal mask which unblock SIGINT
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        err_sys("SIG_SETMASK error");
    }

    // and continue processing...
    pr_mask("program exit: ");
    exit(0);
}

static void sig_int(int signo) { pr_mask("\nin sig_int: "); }

/**
 *   @file     10.29.c
 *   @date     2019-10-28
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Implementation of the POSIX.1 sleep function
 *
 *  modification of figure 10.17, hands signals reliably
 *  avoiding the race condition in the earlier implementation
 *
 */

#include "apue.h"

static void sig_alrm(int signo) {
    // nothing to do, just return wakes up sigsuspend()
}

unsigned int sleep(unsigned int seconds) {
    struct sigaction newact, oldact;
    sigset_t         newmask, oldmask, suspmask;
    unsigned int     unslept;

    newact.sa_handler = sig_alrm;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM, &newact, &oldact);

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGALRM);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);

    alarm(seconds);
    suspmask = oldmask;

    sigdelset(&suspmask, SIGALRM);

    sigsuspend(&suspmask);

    unslept = alarm(0);

    sigaction(SIGALRM, &oldact, NULL);

    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    return (unslept);
}

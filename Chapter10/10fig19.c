/**
 *   @file     10fig19.c
 *   @date     2019-10-27
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    The signal_intr function
 *   tries to prevent any interrupted system calls from being restarted.
 */

#include "apue.h"

Sigfunc *signal_intr(int signo, Sigfunc *func) {
    struct sigaction act, oact;
    char             signame[32] = {0};

    psignal(signo, signame);

    printf("%s is caught\n", signame);

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
    if (sigaction(signo, &act, &oact) < 0) {
        return SIG_ERR;
    }
    return (oact.sa_handler);
}

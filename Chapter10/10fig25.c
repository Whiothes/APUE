/**
 *   @file     10fig25.c
 *   @date     2019-10-28
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Implementation of POSIX.1 abort
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// POSIX-style abort() function
void abort(void) {
    sigset_t         mask;
    struct sigaction action;

    // caller can't ignore SIGABRT, if so reset to defautl
    sigaction(SIGABRT, NULL, &action);
    if (action.sa_handler == SIG_IGN) {
        action.sa_handler = SIG_DFL;
        sigaction(SIGABRT, &action, NULL);
    }
    if (action.sa_handler == SIG_DFL) {
        fflush(NULL);  // flush all open stdio streams
    }

    // caller can't block SIGABRT; make sure it's unblocked
    sigfillset(&mask);
    sigdelset(&mask, SIGABRT);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);

    // if we're here, process caught SIGABRT and returned
    fflush(NULL);
    action.sa_handler = SIG_DFL;
    sigaction(SIG_DFL, &action, NULL);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);
    exit(1);
}

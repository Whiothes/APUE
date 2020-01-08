/**
 *   @file     10fig14.c
 *   @date     2019-10-27
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Print the signal mask for the process
 *
 *   shows a function that prints the names of the signals in the signal mask of
 * the calling process.
 */

#include <errno.h>

#include "apue.h"
void pr_mask(const char *str) {
    sigset_t sigset;
    int      errno_save;

    errno_save = errno;  // we can be canceld by signal handlers

    if (sigprocmask(0, NULL, &sigset) < 0) {
        err_ret("sigprocmask error");
    } else {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT)) {
            printf(" SIGINT");
        }
        if (sigismember(&sigset, SIGQUIT)) {
            printf(" SIGQUIT");
        }
        if (sigismember(&sigset, SIGUSR1)) {
            printf(" SIGUSR1");
        }
        if (sigismember(&sigset, SIGALRM)) {
            printf(" SIGGALRM");
        }

        printf("\n");
    }

    errno = errno_save;
}

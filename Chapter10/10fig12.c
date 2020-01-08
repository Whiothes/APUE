/**
 *   @file     10fig12.c
 *   @date     2019-10-26
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    implementations
 *
 *  An implementation of sigaddset(), sigdelset(), sigismember()
 *
 */
#include <errno.h>
#include <signal.h>

/**
 * <signal.h> usually defines NSIG to include signal number 0.
 */
#define SIGBAD(signao) ((signo) <= 0 || (signo) >= NSIG)

int my_sigaddset(sigset_t *set, int signo) {
    if (SIGBAD(signo)) {
        errno = EINVAL;
        return (-1);
    }

    *set |= 1 << (signo - 1);  // turn bit on

    return (0);
}

int my_sigdelset(sigset_t *set, int signo) {
    if (SIGBAD(signo)) {
        errno = EINVAL;
        return (-1);
    }

    *set &= ~(1 << (signo - 1));  // turn bit off

    return (0);
}

int my_sigismember(const sigset_t *set, int signo) {
    if (SIGBAD(signo)) {
        errno = EINVAL;
        return (-1);
    }

    return ((*set & (1 << (signo - 1))) != 0);
}

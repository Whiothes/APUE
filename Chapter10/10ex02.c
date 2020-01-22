/**
 *   @file     10ex02.c
 *   @date     2019-10-28
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    example code for 10.2
 */
#include "apue.h"

int sig2str(int signo, char *str) {
    if (signo <= 0 || signo >= NSIG) {
        return -1;
    }
    snprintf(str, SIG2STR_MAX, "%s", sys_siglist[signo]);

    return 0;
}

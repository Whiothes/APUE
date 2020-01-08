/**
 *   @file     09fig12.c
 *   @date     2019-12-09
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Creating an orphaned process group
 */

#include <errno.h>

#include "apue.h"

static void sig_hup(int signo) {
    printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids(char *name) {
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n", name,
           (long)getpid(), (long)getppid(), (long)getpgrp(),
           (long)tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int main(void) {
    char c;
    pid_t pid;

    pr_ids("parent");
    pid = fork();
    switch(pid) {
    case -1:
        err_sys("fork error");

    case 0:
        pr_ids("child");
        signal(SIGHUP, sig_hup);
        kill(getpid(), SIGTSTP);
        pr_ids("child");
        if (read(STDIN_FILENO, &c, 1) != 1) {
            printf("read error %d on controlling TTY\n", errno);
        }

    default:
        sleep(5);
    }

    exit(0);
}

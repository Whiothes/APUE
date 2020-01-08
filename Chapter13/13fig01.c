/**
 *   @file     13fig01.c
 *   @date     2019-11-28
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    a function that can be called from a program
 *             that wants to initialize itsef as a daemon
 */
#include <fcntl.h>
#include <sys/resource.h>
#include <syslog.h>
#include <unistd.h>

#include "apue.h"

extern char *__progname;

void daemonize(const char *cmd) {
    int              i, fd0, fd1, fd2;
    pid_t            pid;
    struct rlimit    rl;
    struct sigaction sa;

    if (cmd == NULL) {
        cmd = __progname;
    }

    // clear file creation mask.
    umask(0);

    // get maximum number of file descriptors
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        err_quit("%s: can't get file limit", cmd);
    }

    // become a session leader to lose controlling TTY.
    if ((pid = fork()) < 0) {
        err_quit("%s: can't fork", cmd);
    } else if (pid != 0) {
        exit(0);  // parent
    }

    setsid();

    // ensure future opens won't allocate controlling TTYs.
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        err_quit("%s: can't ignore SIGHUP", cmd);
    if ((pid = fork()) < 0) {
        err_quit("%s: can't fork", cmd);
    } else if (pid != 0) {
        // parent
        exit(0);
    }

    // change the current working directory to the root so
    // we won't prevent file systems from being unmounted.
    if (chdir("/") < 0) {
        err_quit("%s: can't change directory to /", cmd);
    }

    chroot("/");

    // close all open file descriptors
    if (rl.rlim_max == RLIM_INFINITY) {
        rl.rlim_max = 1024;
    }
    for (i = 0; i < rl.rlim_max; ++i) {
        close(i);
    }

    // attach file descriptors 0, 1 and 2 to /dev/null
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    // initialize the log file
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
}

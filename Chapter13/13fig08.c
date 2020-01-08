/**
 *   @file     13fig08.c
 *   @date     2019-12-01
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    single-threaded daemon can catch SIGHUP and reread its configuration file.
 */

#include "apue.h"
#include <syslog.h>
#include <errno.h>


extern int lockfile(int);
extern int already_running(void);

void reread(void) {
    // ...
}

void sigterm(int signo) {
    syslog(LOG_INFO, "got SIGTERM; exiting");
    exit(0);
}

void sighup(int signo) {
    syslog(LOG_INFO, "Re-reading configuration file");
    reread();
}

int main(int argc, char *argv[]) {
    char             *cmd;
    struct sigaction  sa;

    if ((cmd = strchr(argv[0], '/')) == NULL)
        cmd = argv[0];
    else
        cmd++;

    // become a daemon
    daemonize(cmd);

    if (already_running()) {
        syslog(LOG_ERR, "daemon already running");
        exit(EXIT_FAILURE);
    }

    sa.sa_handler = sigterm;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGHUP);
    sa.sa_flags = 0;
    if ((sigaction(SIGTERM, &sa, NULL)) < 0) {
        syslog(LOG_ERR, "can't catch SIGTERM: %m");
        exit(EXIT_FAILURE);
    }

    sa.sa_handler = sighup;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGTERM);
    sa.sa_flags = 0;
    if ((sigaction(SIGHUP, &sa, NULL)) < 0) {
        syslog(LOG_ERR, "can't catch SIGHUP: %m");
        exit(EXIT_FAILURE);
    }

    exit(0);
}

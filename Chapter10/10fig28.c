/**
 *   @file     10fig28.c
 *   @date     2019-10-28
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Correct POSIX.1 implementation of system function
 *
 *  implementation of the system function with the required signal handling
 *
 */
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "apue.h"

// with appropriate signal handling
int system(const char *cmdstring) {
    pid_t            pid;
    int              status;
    struct sigaction ignore, saveintr, savequit;
    sigset_t         chldmask, savemask;

    if (cmdstring == NULL) {
        return (1);  // always a command processor with UNIX
    }

    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;

    if (sigaction(SIGINT, &ignore, &saveintr) < 0) return (-1);
    if (sigaction(SIGQUIT, &ignore, &savequit) < 0) return (-1);

    sigemptyset(&chldmask);
    sigaddset(&chldmask, SIGCHLD);
    if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0) return (-1);

    if ((pid = fork()) < 0) {
        status = -1;
    } else if (pid == 0) {
        // restore previous signal actions & reset signal mask
        sigaction(SIGINT, &saveintr, NULL);
        sigaction(SIGQUIT, &savequit, NULL);
        sigprocmask(SIG_SETMASK, &savemask, NULL);

        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127);  // exec error
    } else {
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1;  // error other than EINTR from waitpid()
                break;
            }
        }
    }

    // restore previous signal actions & reset signal mask
    if (sigaction(SIGINT, &saveintr, NULL) < 0) return (-1);
    if (sigaction(SIGQUIT, &savequit, NULL) < 0) return (-1);
    if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0) return (-1);

    return (status);
}

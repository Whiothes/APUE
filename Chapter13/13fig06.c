/**
 *   @file     13fig06.c
 *   @date     2019-11-29
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    figure 13.6
 *
 *  illustrates the use of file and record locking
 *  to ensure that only one coyp of a daemon is running
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

extern int lockfile(int);

int already_running(void) {
    int  fd;
    char buf[16];

    fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKFILE);
    if (fd < 0) {
        syslog(LOG_ERR, "can't open %s: %m", LOCKFILE);
        exit(EXIT_FAILURE);
    }

    if (lockfile(fd) < 0) {
        if (errno == EACCES || errno == EAGAIN) {
            close(fd);
            return (1);
        }
        syslog(LOG_ERR, "can't lock %s: %m", LOCKFILE);
        exit(EXIT_FAILURE);
    }

    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, "%ld", strlen(buf) + 1);

    return (0);
}

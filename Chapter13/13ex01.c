/**
 *   @file     13ex01.c
 *   @date     2019-12-01
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    test chroot before openlog
 */

#include <syslog.h>

#include "apue.h"

extern char *__progname;

int main() {
    daemonize(__progname);
    syslog(LOG_INFO, "hello world");
}

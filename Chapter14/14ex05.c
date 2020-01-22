/**
 *   @file     14ex05.c
 *   @date     2019-12-29
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    wait for specified number of microseconds via select
 */

#include <sys/poll.h>
#include <sys/select.h>

#include "apue.h"

void sleep_us_select(unsigned int nusecs) {
    struct timeval tval;

    tval.tv_sec  = nusecs / 10e6;
    tval.tv_usec = nusecs % (unsigned int)10e6;
    select(0, NULL, NULL, NULL, &tval);
}

void sleep_us_poll(unsigned int nusecs) {
    struct pollfd fds;
    int           timeout;

    timeout = nusecs / 10e3;
    timeout = timeout <= 0 ? 1 : timeout;

    poll(&fds, 0, timeout);
}

int main() {
    setbuf(stdout, NULL);

    printf("before select sleep\n");
    sleep_us_select(2 * 10e6);
    printf("after select sleep\n");

    printf("before poll sleep\n");
    sleep_us_poll(2 * 10e6);
    printf("after poll sleep\n");
}

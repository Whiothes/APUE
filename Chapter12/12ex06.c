/**
 *   @file     10.29.c
 *   @date     2019-10-28
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    implementation of sleep using select
 */

#include "apue.h"

unsigned int sleep(unsigned int seconds) {
    int            n;
    unsigned int   slept;
    time_t         start, end;
    struct timeval tv;

    tv.tv_sec  = seconds;
    tv.tv_usec = 0;

    time(&start);
    n = select(0, NULL, NULL, NULL, &tv);
    if (n == 0) {
        return 0;
    }
    time(&end);
    slept = end - start;
    if (slept >= seconds) return 0;

    return seconds - slept;
}

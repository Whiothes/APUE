/**
 *   @file     15ex10.c
 *   @date     2020-01-17
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    read and write a FIFO
 */
#include <fcntl.h>

#include "apue.h"

#define TMPFIFO "/tmp/tmp.fifo"

int main() {
    int fr, fw;

    if (mkfifo(TMPFIFO, FILE_MODE) < 0) {
        err_sys("mkfifo error");
    }

    if ((fr = open(TMPFIFO, O_RDONLY | O_NONBLOCK)) < 0) {
        // non-block for avoiding deadlock
        err_sys("open error");
    }

    if ((fw = open(TMPFIFO, O_WRONLY)) < 0) {
        err_sys("open error");
    }

    clr_fl(fr, O_NONBLOCK);
}

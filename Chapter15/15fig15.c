/**
 *   @file     15fig15.c
 *   @date     2020-01-07
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Invoke uppercase/lowercase filter to read commands
 */

#include <sys/wait.h>

#include "apue.h"

int main(void) {
    char  line[MAXLINE];
    FILE *fpin;

    if ((fpin = popen("../bin/15fig14", "r")) == NULL) {
        err_sys("popen error");
    }
    for (;;) {
        fputs("prompt> ", stdout);
        fflush(stdout);
        if (fgets(line, MAXLINE, fpin) == NULL) {
            break;
        }
        if (fputs(line, stdout) == EOF) {
            err_sys("fputs error to pipe");
        }
    }

    if (pclose(fpin) == -1) {
        err_sys("pclose error");
    }
    putchar('\n');
    exit(0);
}

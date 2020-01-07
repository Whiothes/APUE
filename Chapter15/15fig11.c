/**
 *   @file     15fig11.c
 *   @date     2020-01-07
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    copy file to pager program using popen
 */

#include <sys/wait.h>

#include "apue.h"

#define PAGER "${PAGER:-more}"  // environment variable, or default

extern char *__progname;

int main(int argc, char *argv[]) {
    char  line[MAXLINE];
    FILE *fpin, *fpout;

    if (argc != 2) {
        err_quit("usage: %s <pathname>", __progname);
    }
    if ((fpin = fopen(argv[1], "r")) == NULL) {
        err_sys("open %s error", argv[1]);
    }

    if ((fpout = popen(PAGER, "w")) == NULL) {
        err_sys("popen error");
    }

    while (fgets(line, MAXLINE, fpin) != NULL) {
        if (fputs(line, fpout) == EOF) {
            err_sys("fputs error to pipe");
        }
    }

    if (ferror(fpin)) {
        err_sys("fgets error");
    }
    if (fclose(fpin)) {
        err_sys("fclose error");
    }
    if (pclose(fpout) == -1) {
        err_sys("pclose error");
    }

    return 0;
}

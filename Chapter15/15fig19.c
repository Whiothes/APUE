/**
 *   @file     15fig19.c
 *   @date     2020-01-08
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    filter to add two numbers, using standard I/O
 */

#include "apue.h"

int main(void) {
    int  int1, int2;
    char line[MAXLINE];

// since the stdin is a pipe, defaults to fully buffered
// it is blocked reading from stdin
// 15fig18 is blocked reading from pipe
#if 0
    // method 1: no buffer to fix blocking
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
#else
    // OR method 2: line buffer to fix blocking
    setvbuf(stdin, NULL, _IOLBF, 0);
    setvbuf(stdout, NULL, _IOLBF, 0);
#endif

    while (fgets(line, MAXLINE, stdin) != NULL) {
        if (sscanf(line, "%d%d", &int1, &int2) == 2) {
            if (printf("%d\n", int1 + int2) == EOF) {
                err_sys("printf error");
            }
        } else {
            if (printf("invalid args\n") == EOF) {
                err_sys("printf error");
            }
        }
    }
}

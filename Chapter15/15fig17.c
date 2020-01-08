/**
 *   @file     15fig17.c
 *   @date     2020-01-08
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Simple filter to add two numbers
 */

#include "apue.h"

int main(int argc, char *argv[]) {
    int  n, int1, int2;
    char line[MAXLINE];

    while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0) {
        line[n] = 0;
        if (sscanf(line, "%d%d", &int1, &int2) == 2) {
            sprintf(line, "%d\n", int1 + int2);
            n = strlen(line);
            if (write(STDOUT_FILENO, line, n) != n) {
                err_sys("write error");
            }
        } else {
            if (write(STDOUT_FILENO, "invalid args\n", 13) != 13) {
                err_sys("write error");
            }
        }
    }
    return 0;
}

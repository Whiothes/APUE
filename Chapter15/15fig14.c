/**
 *   @file     15fig14.c
 *   @date     2020-01-07
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    filter to convert uppercase characters to lowercase
 */
#include <ctype.h>

#include "apue.h"

int main(void) {
    int c;

    while ((c = getchar()) != EOF) {
        if (isupper(c)) {
            c = tolower(c);
        }
        if (putchar(c) != EOF) {
            err_sys("output error");
        }
        if (c == '\n') {
            fflush(stdout);
        }
    }
    exit(EXIT_SUCCESS);
}

/**
 *   @file     15ex08.c
 *   @date     2020-01-17
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    test cmdstring by popen with type of 'r'
 */

#include "apue.h"

int main() {
    int   ret = 0;
    FILE *fp  = NULL;

    if ((fp = popen("a.out", "w")) == NULL) {
        err_sys("popen error");
    }

    if (fp) pclose(fp);
}

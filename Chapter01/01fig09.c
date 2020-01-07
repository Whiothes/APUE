/**
 *   @file     uidgid.c
 *   @date     2019-12-01
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    print uid and gid
 */

#include "apue.h"

int main(void) {
    printf("uid = %d, gid = %d\n", getuid(), getgid());
    exit(EXIT_SUCCESS);
}

/**
 *   @file     15ex03.c
 *   @date     2020-01-15
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    test popen for non-existent command
 */

#include "apue.h"


int main() {
    FILE *pret = NULL;
    if ((pret = popen("./a.out", "r")) == NULL) {
        perror("popen");
    }
}

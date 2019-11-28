#include "apue.h"

int main(void) {
    int c;

    while ((c = getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF)
            err_sys("output error: %s", strerror(errno));
    }

    if (ferror(stdin)) err_sys("input error: %s", strerror(errno));

    return 0;
}

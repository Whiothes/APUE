#include "apue.h"

int main(int argc, char *argv[argc]) {
    char buf[MAXLINE];

    while (fgets(buf, MAXLINE, stdin) != NULL)
        if (fputs(buf, stdout) == EOF) err_sys("output error");

    if (ferror(stdin)) err_sys("input error: %s", strerror(errno));

    return 0;
}

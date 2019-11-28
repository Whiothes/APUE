#include "apue.h"

#ifdef MAXLINE
#undef MAXLINE
#define MAXLINE 4
#endif

int main(int argc, char *argv[argc]) {
    char buf[MAXLINE];
    int  i = 0;

    printf("MAXLINE: %d\n", MAXLINE);

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (fputs(buf, stdout) == EOF) err_sys("output error");
        ++i;
    }
    int nums = printf("loop_time: %d\n", i);
    printf("nums: %d\n", nums);

    if (ferror(stdin)) err_sys("input error: %s", strerror(errno));

    return 0;
}

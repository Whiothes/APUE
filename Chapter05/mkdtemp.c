#include "apue.h"

void make_temp(char *template);

int main(int argc, char *argv[argc]) {
    char  good_template[] = "/tmp/dirXXXX";  /* right way */
    char *bad_template    = "/tmp/dir/XXXX"; /* bad way */

    printf("trying to create first temp file ...\n");
    make_temp(good_template);
    printf("trying to create second temp file ...\n");
    make_temp(bad_template);
    return 0;
}

void make_temp(char *template) {
    int         fd;
    struct stat sbuf;

    if ((fd = mkstemp(template)) < 0)
        err_sys("create temp: %s\n", strerror(errno));
    printf("temp name = %s\n", template);
    close(fd);

    if (stat(template, &sbuf) < 0) {
        err_sys("stat: %s\n", strerror(errno));
    } else {
        printf("file exists\n");
        unlink(template);
    }
}

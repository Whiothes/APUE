#include <fcntl.h>

#include "apue.h"

int main(int argc, char *argv[]) {
    int         in, out;
    char        buf[BUFSIZ];
    struct stat stbuf = {0};

    size_t l_size;
    if (stat("src.txt", &stbuf) < 0) {
        err_sys("stat: %s", strerror(errno));
    }
    l_size = stbuf.st_size;

    if ((in = open("src.txt", O_RDONLY)) < 0 ||
        (out = open("dst.txt", O_CREAT | O_RDWR, FILE_MODE)) < 0) {
        err_sys("open: %s", strerror(errno));
    }

    size_t l_sum = 0;
    size_t l_cur = 0;

    while ((l_cur = read(in, buf, BUFSIZ)) > 0) {
        l_sum += l_cur;
        if (write(out, buf, l_cur) != l_cur) {
            err_sys("write: %s", strerror(errno));
        }
    }

    close(in);
    close(out);

    return 0;
}

#include <fcntl.h>

#include "apue.h"

int main(int argc, char *argv[argc]) {
    int  fd           = 0;
    int  ret          = 0;
    char buf[MAXLINE] = {0};

    fd = open("./a.txt", O_CREAT | O_RDWR | O_APPEND);
    if (fd < 0) {
        err_sys("open: %s", strerror(errno));
    }

    ret = write(fd, "hello world", 11);
    if (ret < 0) {
        err_sys("write: %s", strerror(errno));
    }

    ret = lseek(fd, 0, SEEK_SET);
    while ((ret = read(fd, buf, MAXLINE))) {
        ;
    }
    if (ret == -1) {
        err_sys("read: %s", strerror(errno));
    }
    printf("read: %s\n", buf);

    ret = lseek(fd, -18, SEEK_CUR);
    ret = write(fd, "hello world", 11);
    if (ret < 0) {
        err_sys("write: %s", strerror(errno));
    }

    ret = lseek(fd, 0, SEEK_SET);
    while ((ret = read(fd, buf, MAXLINE)) > 0) {
        ;
    }
    if (ret == -1) {
        err_sys("read: %s", strerror(errno));
    }
    printf("read: %s\n", buf);

    ret = lseek(fd, 10, SEEK_SET);
    while ((ret = read(fd, buf, MAXLINE)) > 0) {
        ;
    }
    if (ret == -1) {
        err_sys("read: %s", strerror(errno));
    }
    printf("read: %s\n", buf);

    return 0;
}

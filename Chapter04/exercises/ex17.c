#include <fcntl.h>

#include "apue.h"

int main(int argc, char *argv[argc]) {
    char *path = "/dev/fd/1";
    int   fd;
    int   ret;

    if ((ret = unlink(path)) < 0) {
        err_quit("unlink: %s\n", strerror(errno));
    }

    if ((fd = creat(path, FILE_MODE)) < 0) {
        err_quit("creat: %s\n", strerror(errno));
    }
    return 0;
}

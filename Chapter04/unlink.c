#include <errno.h>
#include <fcntl.h>

#include "apue.h"

int main(int argc, char *argv[]) {
    if (open("tempfile", O_RDWR) < 0) {
        err_sys("open: %s", strerror(errno));
    }
    if (unlink("tempfile") < 0) {
        err_sys("unlink: %s", strerror(errno));
    }
    printf("file unlinked\n");
    sleep(15);
    printf("done\n");
    return 0;
}

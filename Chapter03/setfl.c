#include <fcntl.h>

#include "apue.h"

void set_fl(int fd, int flags) /* flags are file status flags to turn on */

{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        err_sys("fcntl F_GETFL: %s", strerror(errno));
    }

    val |= flags; /* turn on flags */

    if (fcntl(fd, F_SETFL, val) < 0) {
        err_sys("fcntl F_SETFL: %s", strerror(errno));
    }
}

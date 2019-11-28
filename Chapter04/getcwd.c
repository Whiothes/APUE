#include "apue.h"

int main(int argc, char *argv[argc]) {
    char * ptr;
    size_t size;

    if (chdir("/usr/local") < 0) {
        err_sys("chdir: %s\n", strerror(errno));
    }

    ptr = path_alloc(&size);
    if (getcwd(ptr, size) == NULL) {
        err_sys("getcwd: %s\n", ptr);
    }

    printf("cwd = %s\n", ptr);

    return 0;
}

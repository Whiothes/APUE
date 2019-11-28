#include "apue.h"

int main(int argc, char *argv[argc]) {
    if (chdir("/tmp") < 0) {
        perror("chdir: ");
    }
    printf("chdir to /tmp SUCCESS\n");
    return 0;
}

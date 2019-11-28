#include "apue.h"

int main(int argc, char *argv[]) {
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
        printf("%s\n", strerror(errno));
    } else {
        printf("seek OK\n");
    }

    return 0;
}

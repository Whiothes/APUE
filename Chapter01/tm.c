#include <time.h>

#include "apue.h"

int main(int argc, char *argv[]) {
    int i = 0;

    for (i = 0; i < __INT_MAX__; ++i) {
        if (i % (2 * 1024) == 0) {
            printf("%d\n", _SC_CLK_TCK);
        }
    }

    return 0;
}

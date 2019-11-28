#include <math.h>

#include "apue.h"

int main(int argc, char *argv[]) {
    printf("%d, %d\n", __INT_MAX__, (int)pow(2, 31) - 1);
    return 0;
}

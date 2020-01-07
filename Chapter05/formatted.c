#include <locale.h>

#include "apue.h"

int main(void) {
    printf("\nthousands grouping:\n");
    setlocale(LC_ALL, "en_US.UTF-8");
    printf("%'d\n", 1000000);

    printf("\nleft-justify:\n");
    printf("%-d\t%-d\n", 901290, 1290);
    printf("%-d\t%-d\n", 92103, 13093);

    printf("\nalways signed:\n");
    printf("%+d\n", 1000);

    printf("\nspace prefix:\n");
    printf("% d\n", 1000);

    printf("\nalternative form:\n");
    printf("%#x\n", 1000);

    printf("\nprefix zero:\n");
    printf("%010d\n", 1000);

    printf("\nsigned decimal:\n");
    printf("%i\n", 1000);
    printf("%d\n", 1000);

    printf("\nunsigned octal:\n");
    printf("%o\n", 1000);

    printf("\nunsigned decimal:\n");
    printf("%u\n", 1000);

    printf("\nunsigned hexadecimal:\n");
    printf("%x, %X\n", 1000, 1000);

    printf("\ndouble floating-point number:\n");
    printf("%f, %F\n", 1000.0, 1000.0);

    printf("\nexponential format:\n");
    printf("%e, %E\n", 1000.0, 1000.0);

    printf("\ninterpreted:\n");
    printf("%g, %G\n", 1000.0, 100000000000.0);

    printf("\ndouble in hexadecimal:\n");
    printf("%a, %A\n", 1000.0, 100000000000.0);
}

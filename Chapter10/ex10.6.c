/**
 *   @file     exx10.6.c
 *   @date     2019-10-29
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    test figure 10.24
 */

#include "apue.h"

int main(void) {
    FILE *fp = fopen("a.txt", "w+");

    int num = 0;

    fwrite(&num, sizeof(num), 1, fp);

    pid_t pid = fork();

    if (pid == 0) {
        // fread(&num, sizeof(num), 1, fp);
        ++num;
        fwrite(&num, sizeof(num), 1, fp);
        fprintf(stdout, "child process: %d\n", num);
        exit(EXIT_SUCCESS);
    }

    // fread(&num, sizeof(num), 1, fp);
    ++num;
    fwrite(&num, sizeof(num), 1, fp);
    fprintf(stdout, "parent process: %d\n", num);

    fclose(fp);
}

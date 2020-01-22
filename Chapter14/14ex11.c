/**
 *   @file     14ex11.c
 *   @date     2019-12-29
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    rewrite 14fig27
 *
 *  close fd after calling mmap
 *
 */

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h>

#include "apue.h"

#define COPYINCR (1024 * 1024 * 1024)  // 1GB

int main(int argc, char *argv[]) {
    int         fdin, fdout;
    void *      src, *dst;
    size_t      copysz;
    struct stat sbuf;
    off_t       fsz = 0;

    if (argc != 3) {
        err_quit("usage: %s <from-file> <to-file>", argv[0]);
    }

    if ((fdin = open(argv[1], O_RDONLY)) < 0) {
        err_sys("can't open %s for reading", argv[1]);
    }

    if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0) {
        err_sys("can't create %s for writting", argv[2]);
    }

    if (fstat(fdin, &sbuf) < 0) {
        err_sys("fstat error");
    }

    // If we don’t set the output file’s size, the call to mmap for the output
    // file is successful, but the first reference to the associated memory
    // region generates a SIGBUS signal.
    if (ftruncate(fdout, sbuf.st_size) < 0) {
        err_sys("ftruncate error");
    }

    while (fsz < sbuf.st_size) {
        if ((sbuf.st_size - fsz) > COPYINCR) {
            copysz = COPYINCR;
        } else {
            copysz = sbuf.st_size - fsz;
        }

        if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED, fdin, fsz)) ==
            MAP_FAILED) {
            err_sys("mmap error for input");
        }
        // calling close fd to verify
        close(fdin);


        if ((dst = mmap(0, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, fdout,
                        fsz)) == MAP_FAILED) {
            err_sys("mmap error for output");
        }
        close(fdout);

        memcpy(dst, src, copysz);

        munmap(src, copysz);
        munmap(dst, copysz);
        fsz += copysz;
    }
}

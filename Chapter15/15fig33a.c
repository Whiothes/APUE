/**
 *   @file     15fig33a.c
 *   @date     2020-01-10
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    IPC between parent and child using memory mapped I/O of /dev/zero
 *            use anoynymous facility
 */
#include <fcntl.h>
#include <sys/mman.h>

#include "apue.h"

#define NLOOPS 1000
#define SIZE   sizeof(long)  // size of shared memory area

static int update(long *ptr) {
    return ((*ptr)++);  // return value before increment
}

int main(void) {
    int   fd, i, counter;
    pid_t pid;
    void *area;

    // if ((fd = open("/dev/zero", O_RDWR)) < 0) {
    //     err_sys("open error");
    // }
    fd = -1;

    // if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) ==
    // MAP_FAILED) {
    if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, fd,
                     0)) == MAP_FAILED) {
        err_sys("mmap error");
    }
    // close(fd);

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) { /* parent */
        for (i = 0; i < NLOOPS; i += 2) {
            if ((counter = update((long *)area)) != i)
                err_quit("parent: expected %d, got %d", i, counter);

            TELL_CHILD(pid);
            WAIT_CHILD();
        }
    } else { /* child */
        for (i = 1; i < NLOOPS + 1; i += 2) {
            WAIT_PARENT();

            if ((counter = update((long *)area)) != i)
                err_quit("child: expected %d, got %d", i, counter);

            TELL_PARENT(getppid());
        }
    }
}

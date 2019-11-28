#include "apue.h"

ssize_t readn(int fd, void *ptr, size_t n) {
    size_t  nleft;
    ssize_t nread;

    nleft = n;
    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (nleft == n) {
                return -1;
            } else {
                break;
            }
        }
        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft);
}

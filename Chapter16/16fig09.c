/**
 *   @file     16fig09.c
 *   @date     2020-01-22
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Print host and service info
 */
#include "apue.h"

#if defined(SOLARIS)
#include <netinet/in.h>
#endif
#include <arpa/inet.h>
#include <netdb.h>
#if defined(BSD)
#include <netinet/in.h>
#include <sys/socket.h>
#endif

void print_family(struct addrinfo *aip) {
    printf(" family ");
    switch (aip->ai_family) {
    case AF_INET:   printf("inet");        break;
    case AF_INET6:  printf("inet6");       break;
    case AF_UNIX:   printf("unix");        break;
    case AF_UNSPEC: printf("unspecified"); break;
    default:        printf("unknown");     break;
    }
}

void print_type(struct addrinfo *aip) {
    printf(" type ");
    switch (aip->ai_socktype) {
    case SOCK_STREAM:    printf("stream");                         break;
    case SOCK_DGRAM:     printf("datagram");                       break;
    case SOCK_SEQPACKET: printf("seqpacket");                      break;
    case SOCK_RAW:       printf("raw");                            break;
    default:             printf("unknown (%d)", aip->ai_socktype); break;
    }
}

void print_protocol(struct addrinfo *aip) {
    printf(" protocol ");
    switch (aip->ai_protocol) {
    case 0:           printf("default");                        break;
    case IPPROTO_TCP: printf("TCP");                            break;
    case IPPROTO_UDP: printf("UDP");                            break;
    case IPPROTO_RAW: printf("raw");                            break;
    default:          printf("unknown (%d)", aip->ai_protocol); break;
    }
}

void print_flags(struct addrinfo *aip) {
    printf("flags:");
    if (aip->ai_flags == 0) {
        printf(" 0");
    } else {
        if (aip->ai_flags & AI_PASSIVE) {
            printf(" passive");
        }
        if (aip->ai_flags & AI_CANONNAME) {
            printf(" canonname");
        }
        if (aip->ai_flags & AI_NUMERICHOST) {
            printf(" numerichost");
        }
        if (aip->ai_flags & AI_NUMERICSERV) {
            printf(" numericserv");
        }
        if (aip->ai_flags & AI_V4MAPPED) {
            printf(" v4mapped");
        }
        if (aip->ai_flags & AI_ALL) {
            printf(" all");
        }
    }
}

int main(int argc, char *argv[]) {
    struct addrinfo *    ailist, *aip;
    struct addrinfo      hint;
    struct sockaddr_in * sinp;
    struct sockaddr_in6 *sinp6;
    const char *         addr;
    int                  err;
    char                 abuf[INET_ADDRSTRLEN];
    char                 abuf6[INET6_ADDRSTRLEN];

    if (argc != 3) {
        err_quit("usage: %s nodename(host) service", argv[0]);
    }
    hint.ai_flags     = AI_CANONNAME;
    hint.ai_family    = 0;
    hint.ai_socktype  = 0;
    hint.ai_protocol  = 0;
    hint.ai_addrlen   = 0;
    hint.ai_canonname = NULL;
    hint.ai_addr      = NULL;
    hint.ai_next      = NULL;

    if ((err = getaddrinfo(argv[1], argv[2], &hint, &ailist)) != 0) {
        err_quit("getaddrinfo error: %s", gai_strerror(err));
    }

    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        print_flags(aip);
        print_family(aip);
        print_type(aip);
        print_protocol(aip);
        printf("\n\thost %s", aip->ai_canonname ? aip->ai_canonname : "-");
        if (aip->ai_family == AF_INET) {
            sinp = (struct sockaddr_in *)aip->ai_addr;
            addr = inet_ntop(AF_INET, &sinp->sin_addr, abuf, INET_ADDRSTRLEN);
            printf(" address %s", addr ? addr : "unknown");
            printf(" port %d", ntohs(sinp->sin_port));
        } else if (aip->ai_family == AF_INET6) {
            sinp6 = (struct sockaddr_in6 *)aip->ai_addr;
            addr =
                inet_ntop(AF_INET6, &sinp6->sin6_addr, abuf6, INET6_ADDRSTRLEN);
            printf(" address %s", addr ? addr : "unknown");
            printf(" port %d", ntohs(sinp6->sin6_port));
        }
        printf("\n");
    }
}

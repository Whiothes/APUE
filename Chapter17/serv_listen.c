#include "apue.h"
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>

#define QLEN 10

/*
 * Create a server endpoint of a connection.
 * Returns fd if all OK, <0 on error.
 */
int serv_listen(const char *name)
{
  int                fd, len, err, rval;
  struct sockaddr_un un;

  if (strlen(name) >= sizeof(un.sun_path)) {
    errno = ENAMETOOLONG;
    return (-1);
  }

  /* create a UNIX domain stream socket */
  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    return (-2);
  }

  /* in case it already exists */
  unlink(name);

  /* fill in socket address structure */
  memset(&un, 0, sizeof(un));
  un.sun_family = AF_UNIX;
  strcpy(un.sun_path, name);
  len = offsetof(struct sockaddr_un, sun_path) + strlen(name);

  /* bind the name to the descriptor */
  if (bind(fd, (struct sockaddr *)&un, len) < 0) {
    rval = -3;
    goto errout;
  }

  if (listen(fd, QLEN) < 0) {
    /* tell kernel we're a server */
    rval = -4;
    goto errout;
  }

  return (fd);

errout:
  err = errno;
  close(fd);
  errno = err;
  return (rval);
}

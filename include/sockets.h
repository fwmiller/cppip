#ifndef __SOCKETS_H
#define __SOCKETS_H

#include <stdint.h>

class socket {
public:
    int socket(int family, int type, int protocol);
    int bind(int sd, const struct sockaddr *myAddr, int addrLength);
    int connect(int sd, struct sockaddr *servAddr, int addrLength);

    int read(int sd, void *buf, uint32_t n);
    int write(int sd, void *buf, uint32_t n);

    int recv(int sd, void *buf, uint32_t n, int flags);
    int recvfrom(int sd, void *buf, uint32_t n, int flags,
                 struct sockaddr *fromAddr, socklen_t *addrLength);

    int send(int sd, void *buf, uint32_t n, int flags);
    int sendto(int sd, void *buf, uint32_t n, int flags,
               struct sockaddr *toAddr, socklen_t addrLength);

    int shutdown(int sd, int howTo);
    int close(int sd);
};

#endif

#ifndef __SOCKETS_H
#define __SOCKETS_H

#include <stdint.h>
#include "buf.h"

class socket {
private:
    int type;
    bufq_t recvq;

public:
    socket(int type);
    int bind(socket *sd, uint16_t port);
    int connect(socket *sd, uint32_t servAddr, uint16_t servPort);

    int read(socket *sd, void *buf, unsigned n);
    int write(socket *sd, void *buf, unsigned n);

    int recv(socket *sd, void *buf, unsigned n, int flags);
    int recvfrom(socket *sd, void *buf, unsigned n, int flags,
                 uint32_t fromAddr, uint16_t fromPort);

    int send(socket *sd, void *buf, unsigned n, int flags);
    int sendto(socket *sd, void *buf, unsigned n, int flags, uint32_t toAddr,
               uint16_t toPort);

    int shutdown(socket *sd, int howTo);
    int close(socket *sd);
};

#endif

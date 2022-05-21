#include "sockets.h"
#include <stdlib.h>
#include "udptab.h"

socket::socket(int type) {
    this->type = type;
}

int
socket::bind(socket *sd, uint16_t port) {
    bufq_t q = udptab.alloc_port(port);
    if (q == NULL)
        return (-1);
    this->recvq = q;
    return 0;
}

int
socket::connect(socket *sd, uint32_t servAddr, uint16_t servPort) {
    return (-1);
}

int
socket::read(socket *sd, void *buf, unsigned n) {
    return (-1);
}

int
socket::write(socket *sd, void *buf, unsigned n) {
    return (-1);
}

int
socket::recv(socket *sd, void *buf, unsigned n, int flags) {
    return (-1);
}

int
socket::recvfrom(socket *sd, void *buf, unsigned n, int flags,
                 uint32_t fromAddr, uint16_t fromPort) {
    return (-1);
}

int
socket::send(socket *sd, void *buf, unsigned n, int flags) {
    return (-1);
}

int
socket::sendto(socket *sd, void *buf, unsigned n, int flags, uint32_t toAddr,
               uint16_t toPort) {
    return (-1);
}

int
socket::shutdown(socket *sd, int howTo) {
    return (-1);
}

int
socket::close(socket *sd) {
    return (-1);
}

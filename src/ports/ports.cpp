#include "ports.h"
#include <stdlib.h>
#include "udptab.h"

port::port() {
    return;
}

int
port::bind(uint16_t portnum) {
    bufq_t q = udptab.alloc_port(portnum);
    if (q == NULL)
        return (-1);
    this->receiveq = q;
    return 0;
}

int
port::length() {
    return (-1);
}

int
port::receive(void *buf, unsigned bufsize) {
    return (-1);
}

int
port::send(void *buf, unsigned len) {
    return (-1);
}

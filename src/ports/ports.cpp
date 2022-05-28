#include "ports.h"

port::port() {
    return;
}

int
port::bind(uint16_t portnum) {
    return (-1);
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

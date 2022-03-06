#include "inq.h"

inq::inq() {
    this->port = 0;
}

uint16_t
inq::get_port() {
    return this->port;
}

void
inq::set_port(uint16_t port) {
    this->port = port;
}

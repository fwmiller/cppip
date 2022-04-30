#include "inq.h"
#include <stdio.h>

inq::inq(int entries, int bufsize) : bufq(entries, bufsize) {
    this->port = 0;
}

void
inq::dump() {
    printf("%5u  %d", this->port, this->get_length());
}

uint16_t
inq::get_port() {
    return this->port;
}

void
inq::set_port(uint16_t port) {
    this->port = port;
}

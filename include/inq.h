#ifndef __INQ_H
#define __INQ_H

#include "byteq.h"

class inq : public byteq {
private:
    uint16_t port;

public:
    inq();
    void dump();
    uint16_t get_port();
    void set_port(uint16_t port);
};

#endif

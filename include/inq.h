#ifndef __INQ_H
#define __INQ_H

#include "buf.h"

class inq : public bufq {
private:
    uint16_t port;

public:
    inq(int entries, int bufsize);
    void dump();
    uint16_t get_port();
    void set_port(uint16_t port);
};

#endif
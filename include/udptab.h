#ifndef __UDPTAB_H
#define __UDPTAB_H

#include "inq.h"

static const int UDPTAB_ENTRIES = 16;

extern class udptab udptab;

class udptab {
private:
    class inq *table[UDPTAB_ENTRIES];

public:
    udptab();
    void dump();
    class inq *find_port(uint16_t port);
    class inq *alloc_port(uint16_t port);
    void free_port(uint16_t port);
};

#endif

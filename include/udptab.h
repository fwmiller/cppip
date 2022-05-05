#ifndef __UDPTAB_H
#define __UDPTAB_H

#include "buf.h"

static const int UDPTAB_ENTRIES = 16;

extern class udptab udptab;

//
// UDP table
//
class udptab {
private:
    uint16_t port[UDPTAB_ENTRIES];
    class bufq *table[UDPTAB_ENTRIES];

public:
    udptab();
    void dump();
    class bufq *find_port(uint16_t port);
    class bufq *alloc_port(uint16_t port);
    void free_port(uint16_t port);
};

#endif

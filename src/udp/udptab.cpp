#include "udptab.h"
#include <stdio.h>
#include <stdlib.h>

class udptab udptab;

udptab::udptab() {
    return;
}

void
udptab::dump() {
	for (int i = 0; i < UDPTAB_ENTRIES; i++)
		if (this->table[i].get_port() != 0) {
			this->table[i].dump();
			printf("\r\n");
		}
}

class inq *
udptab::find_port(uint16_t port) {
    for (int i = 0; i < UDPTAB_ENTRIES; i++)
        if (this->table[i].get_port() == port)
            return &(this->table[i]);
    return NULL;
}

class inq *
udptab::alloc_port(uint16_t port) {
    for (int i = 0; i < UDPTAB_ENTRIES; i++)
        if (this->table[i].get_port() == 0) {
            class inq *q = (class inq *) &(this->table[i]);
            q->set_port(port);
            return q;
        }
    return NULL;
}

void
udptab::free_port(uint16_t port) {
    for (int i = 0; i < UDPTAB_ENTRIES; i++)
        if (this->table[i].get_port() == port) {
            class inq *q = (class inq *) &(this->table[i]);
            q->set_port(0);
            q->clear();
            return;
        }
}

#include <stdlib.h>
#include "udptab.h"

class udptab udptab;

udptab::udptab()
{
	return;
}

void
udptab::dump()
{
	return;
}

class inq *
udptab::find_port(uint16_t port)
{
    for (int i = 0; i < UDPTAB_ENTRIES; i++)
        if (this->table[i].get_port() == port)
            return &(this->table[i]);
    return NULL;
}

class inq *
udptab::alloc_port(uint16_t port)
{
	return NULL;
}

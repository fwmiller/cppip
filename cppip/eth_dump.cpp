#include <stdio.h>
#include "cppip.h"

void
eth::dump()
{
	if (this->buf == nullptr)
		return;

	eth_hdr_t eh = (eth_hdr_t)this->buf;

	printf("ethernet dst ");
	dump_ethaddr(eh->dst);
	printf(" src ");
	dump_ethaddr(eh->src);

	uint16_t ethertype = ntohs(eh->ethertype);
	printf(" type 0x%04x (", ethertype);
	dump_ethertype(ethertype);
	printf(")\r\n");
}
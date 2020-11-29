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

	uint16_t ethertype = net_to_host_order_short(eh->ethertype);
	printf("type 0x%04x (", ethertype);
	if (ethertype < 1536)
		printf("802.3");
	else
		dump_ethertype(ethertype);
	printf(")\r\n");
}
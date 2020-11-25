#include <stdio.h>
#include "cppip.h"

uint16_t
eth::get_ethertype()
{
	if (this->buf == nullptr)
		return 0;

	eth_hdr_t eh = (eth_hdr_t)this->buf;
	return ntohs(eh->ethertype);
}

eth::eth()
{
	this->buf = nullptr;
}

buf_t
eth::get_buf()
{
	return this->buf;
}

void
eth::set_buf(buf_t buf)
{
	this->buf = buf;
}

void
eth::receive()
{
	switch (this->get_ethertype()) {
	case ETHERTYPE_IPV4:
	{
		class ipv4 ip;
		ip.set_buf(this->buf + sizeof(struct eth_hdr));
		ip.dump();
		ip.receive();
	}
	break;
	case ETHERTYPE_ARP:
	case ETHERTYPE_RARP:
	{
		class arp arp;
		arp.set_buf(this->buf + sizeof(struct eth_hdr));
		arp.dump();
		arp.receive();
	}
	break;
	}
}

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
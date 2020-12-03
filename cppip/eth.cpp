#include "cppip.h"

uint16_t
eth::get_ethertype()
{
	if (this->buf == nullptr)
		return 0;

	eth_hdr_t eh = (eth_hdr_t)this->buf;
	return net_to_host_order_short(eh->ethertype);
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
	uint16_t ethertype;

	ethertype = this->get_ethertype();
	if (ethertype < ETH_MTU_SIZE) {
		class ieee802_2 llc;

		llc.set_buf(this->buf + sizeof(struct eth_hdr));
		llc.dump();
		llc.receive();
		return;
	}
	switch (ethertype) {
	case ETHERTYPE_ARP:
	case ETHERTYPE_RARP:
	{
		class arp arp;
		arp.set_buf(this->buf + sizeof(struct eth_hdr));
		arp.dump();
		arp.receive();
	}
	break;
	case ETHERTYPE_IPV4:
	{
		class ipv4 ip;
		ip.set_buf(this->buf + sizeof(struct eth_hdr));
		ip.dump();
		ip.receive();
	}
	break;
	case ETHERTYPE_IPV6:
	{
		class ipv6 ip;
		ip.set_buf(this->buf + sizeof(struct eth_hdr));
		ip.dump();
		ip.receive();
	}
	break;
	}
}
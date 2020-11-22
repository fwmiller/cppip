#include <stdio.h>
#include "cppip.h"

static void dump_ethertype(uint16_t ethertype);

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

uint16_t
eth::get_ethertype()
{
	if (this->buf == nullptr)
		return 0;

	eth_hdr_t eh = (eth_hdr_t)this->buf;
	return ntohs(eh->ethertype);
}

void
eth::dump()
{
	if (this->buf == nullptr)
		return;

	eth_hdr_t eh = (eth_hdr_t)this->buf;

	printf("ethernet dst %02x:%02x:%02x:%02x:%02x:%02x ",
		eh->dst[0], eh->dst[1], eh->dst[2], eh->dst[3], eh->dst[4], eh->dst[5]);
	printf("src %02x:%02x:%02x:%02x:%02x:%02x ",
		eh->src[0], eh->src[1], eh->src[2], eh->src[3], eh->src[4], eh->src[5]);

	uint16_t ethertype = ntohs(eh->ethertype);
	printf("type 0x%04x (", ethertype);
	dump_ethertype(ethertype);
	printf(")\r\n");
}

static void
dump_ethertype(uint16_t ethertype)
{
	switch (ethertype) {
	case ETHERTYPE_IPV4:
		printf("IPv4");
		break;
	case ETHERTYPE_ARP:
		printf("ARP");
		break;
	case ETHERTYPE_RARP:
		printf("RARP");
		break;
	case ETHERTYPE_VLAN:
		printf("802.1Q VLAN");
		break;
	case ETHERTYPE_IPV6:
		printf("IPv6");
		break;
	default:
		printf("UNKNOWN");
	}
}
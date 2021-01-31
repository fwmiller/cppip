#include <pcap.h>
#include <stdio.h>
#include "cppip.h"

static pcap_t* fp = nullptr;
static char errbuf[PCAP_ERRBUF_SIZE];

uint16_t
eth::get_ethertype()
{
	if (this->buf == nullptr)
		return 0;

	eth_hdr_t eh = (eth_hdr_t)this->buf;
	return reverse_byte_order_short(eh->ethertype);
}

eth::eth()
{
	this->buf = nullptr;
#if 0
	if (fp == nullptr)
		fp = pcap_open(
			intf_name,					// Name of the device
			ETH_MTU_SIZE,				// Portion of the packet to capture
			PCAP_OPENFLAG_PROMISCUOUS,	// Promiscuous mode
			1000,						// Read timeout
			NULL,						// Authentication on the remote machine
			errbuf						// Error buffer
		);
#endif
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
		if (dump_enabled)
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
		if (dump_enabled)
			arp.dump();
		arp.receive();
	}
	break;
	case ETHERTYPE_IPV4:
	{
		class ipv4 ip;
		ip.set_buf(this->buf + sizeof(struct eth_hdr));
		if (dump_enabled)
			ip.dump();
		ip.receive();
	}
	break;
	case ETHERTYPE_IPV6:
	{
		class ipv6 ip;
		ip.set_buf(this->buf + sizeof(struct eth_hdr));
		if (dump_enabled)
			ip.dump();
		ip.receive();
	}
	break;
	}
}

void
eth::send(buf_t buf)
{
	return;
}
#include "cppip.h"
#include <pcap/pcap.h>
#include "stats.h"

static pcap_t *fp = nullptr;
static char errbuf[PCAP_ERRBUF_SIZE];

uint16_t eth::get_ethertype()
{
	if (this->buf == nullptr)
		return 0;

	eth_hdr_t
	    eh = (eth_hdr_t) this->buf;
	return reverse_byte_order_short(eh->ethertype);
}

eth::eth()
{
	this->buf = nullptr;
	this->buflen = 0;
#if 0
	if (fp == nullptr)
		fp = pcap_open(intf_name,	// Name of the device
			       ETH_MTU_SIZE,	// Portion of the packet to capture
			       PCAP_OPENFLAG_PROMISCUOUS,	// Promiscuous mode
			       1000,	// Read timeout
			       nullptr,	// Authentication on the remote machine
			       errbuf	// Error buffer
		    );
#endif
}

buf_t eth::get_buf()
{
	return this->buf;
}

void
 eth::set_buf(buf_t buf)
{
	this->buf = buf;
}

unsigned
 eth::get_buflen()
{
	return this->buflen;
}

void
 eth::set_buflen(unsigned buflen)
{
	this->buflen = buflen;
}

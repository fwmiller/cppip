#include <stdio.h>
#include "cppip.h"

udp::udp()
{
	this->buf = nullptr;
}

buf_t
udp::get_buf()
{
	return this->buf;
}

void
udp::set_buf(buf_t buf)
{
	this->buf = buf;
}

void
udp::receive()
{
	if (this->buf == nullptr)
		return;

	udp_hdr_t uh = (udp_hdr_t)this->buf;
	uint8_t* data = this->buf + sizeof(struct udp_hdr);
	unsigned len = net_to_host_order_short(uh->len);

	// Search open UDP sockets for a matching destination port

	// Copy data into socket buffer

	return;
}

void
udp::dump()
{
	if (this->buf == nullptr)
		return;

	udp_hdr_t uh = (udp_hdr_t)this->buf;

	printf("udp dst %u src %u len %u cksum 0x%04x\r\n",
		net_to_host_order_short(uh->dst),
		net_to_host_order_short(uh->src),
		net_to_host_order_short(uh->len),
		net_to_host_order_short(uh->cksum));
	bufdump(this->buf + sizeof(struct udp_hdr), net_to_host_order_short(uh->len));
}
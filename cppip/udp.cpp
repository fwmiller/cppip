#include <stdio.h>
#include <string.h>
#include "cppip.h"

udp::udp()
{
	this->port = 0;
	this->buf = nullptr;
}

uint16_t
udp::get_port()
{
	return this->port;
}

void
udp::set_port(uint16_t port)
{
	this->port = port;
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
}

void
udp::dump()
{
	if (this->buf == nullptr)
		return;

	udp_hdr_t uh = (udp_hdr_t)this->buf;

	printf("udp dst %u src %u len %u cksum 0x%04x\r\n",
		reverse_byte_order_short(uh->dst),
		reverse_byte_order_short(uh->src),
		reverse_byte_order_short(uh->len),
		reverse_byte_order_short(uh->cksum));
	//bufdump(this->buf + sizeof(struct udp_hdr), reverse_byte_order_short(uh->len));
}
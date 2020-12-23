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
	unsigned len = reverse_byte_order_short(uh->len);

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
		reverse_byte_order_short(uh->dst),
		reverse_byte_order_short(uh->src),
		reverse_byte_order_short(uh->len),
		reverse_byte_order_short(uh->cksum));
	bufdump(this->buf + sizeof(struct udp_hdr), reverse_byte_order_short(uh->len));
}
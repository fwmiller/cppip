#include <stdio.h>
#include "socket.h"
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
	class socket s;
	s.set_buf(this->buf + sizeof(struct udp_hdr));
	s.set_len(reverse_byte_order_short(uh->len));
	if (s.bind(nullptr, 0) == 0)
		s.receive();
	s.close();
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
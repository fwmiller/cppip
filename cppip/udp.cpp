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
udp::dump()
{
	if (this->buf == nullptr)
		return;

	udp_hdr_t uh = (udp_hdr_t)this->buf;

	printf("udp dst %u src %u len %u cksum 0x%04x\r\n",
		ntohs(uh->dst), ntohs(uh->src), ntohs(uh->len), ntohs(uh->cksum));
}
#include <stdio.h>
#include "cppip.h"

ipv4::ipv4()
{
	this->buf = nullptr;
}

buf_t
ipv4::get_buf()
{
	return this->buf;
}

void
ipv4::set_buf(buf_t buf)
{
	this->buf = buf;
}

uint8_t
ipv4::get_hdr_len()
{
	if (this->buf == nullptr)
		return 0;

	ipv4_hdr_t ih = (ipv4_hdr_t)this->buf;
	//return (ih->version & 0x0f) * 32 / 8;
	return (ih->version & 0x0f) << 2;
}

uint8_t
ipv4::get_protocol()
{
	if (this->buf == nullptr)
		return 0;

	ipv4_hdr_t ih = (ipv4_hdr_t)this->buf;
	return ih->protocol;
}

void
ipv4::receive()
{
	switch (this->get_protocol()) {
	case IP_PROTO_UDP:
	{
		class udp udp;
		udp.set_buf(this->buf + this->get_hdr_len());
		udp.dump();
		udp.receive();
	}
	break;
	}
}
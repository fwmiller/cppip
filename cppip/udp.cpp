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
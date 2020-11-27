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

void
ipv4::receive()
{
	class udp udp;
	udp.set_buf(this->buf + sizeof(struct ipv4_hdr));
	udp.dump();
	udp.receive();
}
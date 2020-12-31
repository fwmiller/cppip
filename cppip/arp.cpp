#include "cppip.h"

arp::arp()
{
	this->buf = nullptr;
}

buf_t
arp::get_buf()
{
	return this->buf;
}

void
arp::set_buf(buf_t buf)
{
	this->buf = buf;
}

void
arp::receive()
{
	return;
}

void
arp::send_gratuitous()
{
	return;
}
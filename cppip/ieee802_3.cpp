#include "cppip.h"

ieee802_3::ieee802_3()
{
	this->buf = nullptr;
}


buf_t
ieee802_3::get_buf()
{
	return this->buf;
}

void
ieee802_3::set_buf(buf_t buf)
{
	this->buf = buf;
}

void
ieee802_3::receive()
{
	return;
}

void
ieee802_3::dump()
{
	return;
}

#include <stdio.h>
#include "cppip.h"

ieee802_2::ieee802_2()
{
	this->buf = nullptr;
}


buf_t
ieee802_2::get_buf()
{
	return this->buf;
}

void
ieee802_2::set_buf(buf_t buf)
{
	this->buf = buf;
}

void
ieee802_2::receive()
{
	return;
}

void
ieee802_2::dump()
{
	if (this->buf == nullptr)
		return;

	ieee802_2_hdr_t llchdr = (ieee802_2_hdr_t)this->buf;

	printf("802.2 LLC dsap 0x%02x ssap 0x%02x", llchdr->dsap, llchdr->ssap);

	if ((llchdr->control & 0x03) == 0x03)
		printf(" U-format");
	else
		printf(" I/S-format");

	printf("\r\n");
}

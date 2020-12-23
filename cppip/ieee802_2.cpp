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

	ieee802_2_hdr_t llc_hdr = (ieee802_2_hdr_t)this->buf;

	printf("802.2 LLC dsap 0x%02x ssap 0x%02x", llc_hdr->dsap, llc_hdr->ssap);

	if ((llc_hdr->control & 0x03) == 0x03)
		printf(" control 0x%02x (U-format)", llc_hdr->control);
	else {
		uint16_t control;
		control = reverse_byte_order_short(*((uint16_t *) &(llc_hdr->control)));
		printf(" control 0x%04x (I/S-format)", control);
	}
	printf("\r\n");
}

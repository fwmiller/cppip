#include <stdio.h>
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
arp::dump()
{
	if (this->buf == nullptr)
		return;

	arp_hdr_t ah = (arp_hdr_t)this->buf;

	switch (ntohs(ah->opcode)) {
	case ARP_OP_REQ:
		printf("arp who has ");
		break;
	case ARP_OP_REP:
		printf("arp is at ");
		break;
	case RARP_OP_REQ:
		printf("rarp who has ");
		break;
	case RARP_OP_REP:
		printf("rarp is at ");
		break;
	default:
		printf("UNKNOWN");
		break;
	}
	printf("\r\n");
}
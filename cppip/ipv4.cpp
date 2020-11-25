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

void
ipv4::dump()
{
	if (this->buf == nullptr)
		return;

	ipv4_hdr_t ih = (ipv4_hdr_t)this->buf;

	printf("ipv4 version 0x%02x tos 0x%02x len %u id 0x%04x\r\n",
		ih->version, ih->tos, ih->len, ih->id);
	printf(" frag 0x%04x ttl %u protocol 0x%02x hdr cksum 0x%04x\r\n",
		ih->frag, ih->ttl, ih->protocol, ih->hdr_cksum);
	printf(" dst ");
	dump_ipaddr(ntohl(ih->dst));
	printf(" src ");
	dump_ipaddr(ntohl(ih->src));
	printf("\r\n");
}
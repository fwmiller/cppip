#include "cppip.h"

ipv6::ipv6()
{
	this->buf = nullptr;
}

buf_t
ipv6::get_buf()
{
	return this->buf;
}

void
ipv6::set_buf(buf_t buf)
{
	this->buf = buf;
}

void
ipv6::receive()
{
	if (this->buf == nullptr)
		return;

	ipv6_hdr_t ih = (ipv6_hdr_t)this->buf;

	switch (ih->next) {
	case IP_PROTO_IPV6_ICMP:
	{
		class icmpv6 ic;
		ic.set_buf(this->buf + sizeof(struct ipv6_hdr));
		ic.dump();
		ic.receive();
	}
	break;
	}
}
#include <stdio.h>
#include "cppip.h"

static void icmp_dump_type(uint8_t type);

icmpv6::icmpv6()
{
	this->buf = nullptr;
}

buf_t icmpv6::get_buf()
{
	return this->buf;
}

void
 icmpv6::set_buf(buf_t buf)
{
	this->buf = buf;
}

void
 icmpv6::receive()
{
	return;
}

void
 icmpv6::dump()
{
	if (this->buf == nullptr)
		return;

	icmpv6_hdr_t
	    ih = (icmpv6_hdr_t) this->buf;

	printf("icmpv6 type 0x%02x (", ih->type);
	icmp_dump_type(ih->type);
	printf(") code 0x%02x chksum 0x%04x\r\n",
	       ih->code, reverse_byte_order_short(ih->cksum));
}

static void
icmp_dump_type(uint8_t type)
{
	switch (type) {
	case ICMP_TYPE_DEST_UNRCH:
		printf("Desination unreachable");
		break;
	case ICMP_TYPE_PKT_TOO_BIG:
		printf("Packet too big");
		break;
	case ICMP_TYPE_TIME_EXCEEDED:
		printf("Time exceeded");
		break;
	case ICMP_TYPE_PARAM_PROB:
		printf("Parameter problem");
		break;
	case ICMP_TYPE_ECHO_REQ:
		printf("Echo request");
		break;
	case ICMP_TYPE_ECHO_REP:
		printf("Echo reply");
		break;
	case ICMP_TYPE_MLQ:
		printf("Multicast Listener Query");
		break;
	case ICMP_TYPE_MLR:
		printf("Multicast Listener Report");
		break;
	case ICMP_TYPE_MLD:
		printf("Multicast Listener Done");
		break;
	case ICMP_TYPE_ROUTER_SOL:
		printf("Router solicitation");
		break;
	case ICMP_TYPE_ROUTER_AD:
		printf("Router advertisement");
		break;
	case ICMP_TYPE_NEIGHBOR_SOL:
		printf("Neighbor solicitation");
		break;
	case ICMP_TYPE_NEIGHBOR_AD:
		printf("Neighbor advertisement");
		break;
	case ICMP_TYPE_REDIRECT:
		printf("Redirect");
		break;
	case ICMP_TYPE_ROUTER_RENUM:
		printf("Router renumbering");
		break;
	case ICMP_TYPE_NODE_INFO_QUERY:
		printf("Node information query");
		break;
	case ICMP_TYPE_NODE_INFO_RESP:
		printf("Node information response");
		break;
	case ICMP_TYPE_INV_NEIGHBOR_SOL:
		printf("Inverse neighbor discovery solicitation");
		break;
	case ICMP_TYPE_INV_NEIGHBOR_AD:
		printf("Inverse neighbor discovery advertisement");
		break;
	case ICMP_TYPE_MLDR:
		printf("Multicast Listener Discovery Reports");
		break;
	case ICMP_TYPE_HOME_ADDR_DISC_REQ:
		printf("Home agent address discovery request");
		break;
	case ICMP_TYPE_HOME_ADDR_DISC_REP:
		printf("Home agent address discovery reply");
		break;
	case ICMP_TYPE_MOBILE_PREFIX_SOL:
		printf("Mobile prefix solicitation");
		break;
	case ICMP_TYPE_MOBILE_PREFIX_AD:
		printf("Mobile prefix advertisement");
		break;
	case ICMP_TYPE_CERT_PATH_SOL:
		printf("Certification path solicitation");
		break;
	case ICMP_TYPE_CERT_PATH_AD:
		printf("Certification path advertisement");
		break;
	case ICMP_TYPE_MCAST_ROUTER_AD:
		printf("Multicast router advertisement");
		break;
	case ICMP_TYPE_MCAST_ROUTER_SOL:
		printf("Multicast router solicitation");
		break;
	case ICMP_TYPE_MCAST_ROUTER_TERM:
		printf("Multicast router termination");
		break;
	case ICMP_TYPE_RPL_CTL:
		printf("RPL control");
		break;
	default:
		printf("UNKNOWN");
		break;
	}
}

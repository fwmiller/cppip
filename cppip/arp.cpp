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
		dump_ipaddr(ntohl(ah->tpa));
		printf(" tell ");
		dump_ipaddr(ntohl(ah->spa));
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

	printf(" hw 0x%04x (", ntohs(ah->hw));
	switch (ntohs(ah->hw)) {
	case ARP_HW_ETH:
		printf("Ethernet");
		break;
	case ARP_HW_802:
		printf("IEEE 802");
		break;
	case ARP_HW_SER:
		printf("Serial");
		break;
	default:
		printf("UNKNOWN");
		break;
	}
	printf(") proto 0x%04x (", ntohs(ah->proto));
	dump_ethertype(ntohs(ah->proto));
	printf(")\r\n");
	printf(" hw addr len %u proto addr len %u opcode 0x%04x (",
		ah->hw_addr_len, ah->proto_addr_len, ntohs(ah->opcode));
	switch (ntohs(ah->opcode)) {
	case ARP_OP_REQ:
		printf("ARP request");
		break;
	case ARP_OP_REP:
		printf("ARP reply");
		break;
	case RARP_OP_REQ:
		printf("RARP request");
		break;
	case RARP_OP_REP:
		printf("RARP reply");
		break;
	default:
		printf("UNKNOWN");
		break;
	}
	printf(")\r\n");
	printf(" sha ");
	dump_ethaddr((uint8_t *) &(ah->sha));
	printf(" spa 0x%08x (", ntohl(ah->spa));
	dump_ipaddr(ntohl(ah->spa));
	printf(")\r\n");
	printf(" tha ");
	dump_ethaddr((uint8_t*)&(ah->tha));
	printf(" tpa 0x%08x (", ntohl(ah->tpa));
	dump_ipaddr(ntohl(ah->tpa));
	printf(")\r\n");
}
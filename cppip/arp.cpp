#include <string.h>
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
	if (this->buf == nullptr)
		return;

	arp_hdr_t ah = (arp_hdr_t)this->buf;

	switch (reverse_byte_order_short(ah->opcode)) {
	case ARP_OP_REQ:
		break;
	case ARP_OP_REP:
		break;
	}
}

void
arp::send_probe()
{
	// Generate ARP probe packet

	uint8_t buf[ETH_MTU_SIZE];
	memset(buf, 0, ETH_MTU_SIZE);  // Zeros ah->tha
	arp_hdr_t ah = (arp_hdr_t)(buf + sizeof(struct eth_hdr));
	ah->hw = reverse_byte_order_short(ARP_HW_ETH);
	ah->proto = reverse_byte_order_short(ETHERTYPE_ARP);
	ah->hw_addr_len = ETH_ADDR_LEN;
	ah->proto_addr_len = IPV4_ADDR_LEN;
	ah->opcode = reverse_byte_order_short(ARP_OP_REQ);
	memcpy(ah->sha, my_addr->get_ha(), ETH_ADDR_LEN);
	ah->spa = 0;
	ah->tpa = ah->spa;
}

void
arp::send_announce()
{
	// Generate ARP REQ announcement packet
	//  Note: ARP REP announcement method not supported

	uint8_t buf[ETH_MTU_SIZE];
	memset(buf, 0, ETH_MTU_SIZE);  // Zeros ah->tha
	arp_hdr_t ah = (arp_hdr_t)(buf + sizeof(struct eth_hdr));
	ah->hw = reverse_byte_order_short(ARP_HW_ETH);
	ah->proto = reverse_byte_order_short(ETHERTYPE_ARP);
	ah->hw_addr_len = ETH_ADDR_LEN;
	ah->proto_addr_len = IPV4_ADDR_LEN;
	ah->opcode = reverse_byte_order_short(ARP_OP_REQ);
	memcpy(ah->sha, my_addr->get_ha(), ETH_ADDR_LEN);
	ah->spa = reverse_byte_order_short(my_addr->get_pa());
	ah->tpa = ah->spa;
}
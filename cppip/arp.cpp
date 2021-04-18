#include <string.h>
#include "cppip.h"

extern class arptab_entry* my_addr;

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

static void
gen_arp_packet(uint8_t *buf, uint16_t opcode,
	uint8_t *sha, uint32_t spa, uint8_t *tha, uint32_t tpa)
{
	arp_hdr_t ah = (arp_hdr_t)(buf + sizeof(struct eth_hdr));
	ah->hw = reverse_byte_order_short(ARP_HW_ETH);
	ah->proto = reverse_byte_order_short(ETHERTYPE_ARP);
	ah->hw_addr_len = ETH_ADDR_LEN;
	ah->proto_addr_len = IPV4_ADDR_LEN;
	ah->opcode = reverse_byte_order_short(opcode);
	if (sha != nullptr)
		memcpy(ah->sha, sha, ETH_ADDR_LEN);
	ah->spa = spa;
	if (tha != nullptr)
		memcpy(ah->tha, tha, ETH_ADDR_LEN);
	ah->tpa = tpa;
}

void
arp::send_probe()
{
	// Generate ARP probe packet
	uint8_t buf[ETH_MTU_SIZE];
	memset(buf, 0, ETH_MTU_SIZE);  // Zeros ah->tha

	// Leave space for the Ethernet header
	gen_arp_packet(buf + sizeof(struct eth_hdr), ARP_OP_REQ,
		my_addr->get_ha(), 0, nullptr, 0);

	// Format Ethernet header
	memset(buf, 0xff, ETH_ADDR_LEN);
	memcpy(buf + ETH_ADDR_LEN, my_addr->get_ha(), ETH_ADDR_LEN);
	*((uint16_t*)(buf + (ETH_ADDR_LEN << 1))) =
		reverse_byte_order_short(ETHERTYPE_ARP);

	bufdump(buf, sizeof(struct arp_hdr) + sizeof(struct eth_hdr));

	class eth e;
	e.set_buf(buf);
	e.send();
}

void
arp::send_announce()
{
	// Generate ARP REQ announcement packet
	//  Note: ARP REP announcement method not supported
	uint8_t buf[ETH_MTU_SIZE];
	memset(buf, 0, ETH_MTU_SIZE);  // Zeros ah->tha
	gen_arp_packet(buf + sizeof(struct eth_hdr), ARP_OP_REQ,
		my_addr->get_ha(), reverse_byte_order_short(my_addr->get_pa()),
		nullptr, reverse_byte_order_short(my_addr->get_pa()));

	bufdump(buf + sizeof(struct eth_hdr), sizeof(struct arp_hdr));
}
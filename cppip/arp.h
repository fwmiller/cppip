#ifndef __ARP_H
#define __ARP_H

#include <stdint.h>

const static uint16_t ARP_HW_ETH = 0x0001;
const static uint16_t ARP_HW_802 = 0x0006;
const static uint16_t ARP_HW_SER = 0x0014;

const static uint16_t ARP_OP_REQ = 0x0001;
const static uint16_t ARP_OP_REP = 0x0002;
const static uint16_t RARP_OP_REQ = 0x0003;
const static uint16_t RARP_OP_REP = 0x0004;

struct alignas(1) arp_hdr {
	uint16_t hw;
	uint16_t proto;
	uint8_t hw_addr_len;
	uint8_t proto_addr_len;
	uint16_t opcode;
};

typedef struct arp_hdr* arp_hdr_t;

class arp {
private:
	buf_t buf;
public:
	arp();
	buf_t get_buf();
	void set_buf(buf_t buf);
	void dump();
};

#endif
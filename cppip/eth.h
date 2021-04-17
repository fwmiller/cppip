#ifndef __ETHERNET_H
#define __ETHERNET_H

#include "cppip.h"

static const unsigned ETH_MTU_SIZE = 1536;

struct eth_hdr {
	uint8_t dst[ETH_ADDR_LEN];
	uint8_t src[ETH_ADDR_LEN];
	uint16_t ethertype;
};

typedef struct eth_hdr* eth_hdr_t;

class eth {
private:
	buf_t buf;
	uint16_t get_ethertype();
public:
	eth();
	buf_t get_buf();
	void set_buf(buf_t buf);
	void receive();
	void send();
	void dump();
};

#endif
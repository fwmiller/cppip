#ifndef __ETHERNET_H
#define __ETHERNET_H

#include <stdint.h>

#pragma pack(1)
struct eth_hdr {
	uint8_t dst[6];
	uint8_t src[6];
	uint16_t ethertype;
};

typedef struct eth_hdr* eth_hdr_t;

class eth {
private:
	buf_t buf;
public:
	eth();
	buf_t get_buf();
	void set_buf(buf_t buf);
	uint16_t get_ethertype();
	void dump();
};

#endif
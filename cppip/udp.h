#ifndef __UDP_H
#define __UDP_H

#include <stdint.h>
#include "cppip.h"

#pragma pack(1)
struct udp_hdr {
	uint16_t src;
	uint16_t dst;
	uint16_t len;
	uint16_t cksum;
};

typedef struct udp_hdr* udp_hdr_t;

class udp {
private:
	buf_t buf;

public:
	udp();
	buf_t get_buf();
	void set_buf(buf_t buf);
	void receive();
	void dump();
};

#endif
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
	uint16_t port;	// Local port number
	buf_t buf;

public:
	udp();
	uint16_t get_port();
	void set_port(uint16_t port);
	buf_t get_buf();
	void set_buf(buf_t buf);
	void receive();
	void dump();
	int read(buf_t buf, int len);
};

#endif
#ifndef __IPV6_H
#define __IPV6_H

#include <stdint.h>
#include "cppip.h"

#pragma pack(1)
struct ipv6_hdr {
	uint8_t ver_class;
	uint8_t class_flow;
	uint16_t flow_label;
	uint16_t len;
	uint8_t next;
	uint8_t hop_lmt;
	uint8_t src[16];
	uint8_t dst[16];
};

typedef struct ipv6_hdr* ipv6_hdr_t;

class ipv6 {
private:
	buf_t buf;
public:
	ipv6();
	buf_t get_buf();
	void set_buf(buf_t buf);
	void receive();
	void dump();
};

#endif
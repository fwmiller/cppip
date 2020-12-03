#ifndef __IPV4_H
#define __IPV4_H

#include <stdint.h>
#include "cppip.h"
#include "ipv4proto.h"

#pragma pack(1)
struct ipv4_hdr {
	uint8_t version;
	uint8_t tos;
	uint16_t len;
	uint16_t id;
	uint16_t frag;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t hdr_cksum;
	uint32_t src;
	uint32_t dst;
};

typedef struct ipv4_hdr* ipv4_hdr_t;

class ipv4 {
private:
	buf_t buf;
	uint8_t get_hdr_len();
	uint8_t get_protocol();
public:
	ipv4();
	buf_t get_buf();
	void set_buf(buf_t buf);
	void receive();
	void dump();
};

void ipv4_dump_proto(uint8_t proto);

#endif
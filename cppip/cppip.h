#ifndef __CPPIP
#define __CPPIP

#include <stdint.h>

#define WINDOWS_IGNORE_PACKING_MISMATCH

static const unsigned ETH_ADDR_LEN = 6;
static const unsigned IPV4_ADDR_LEN = 4;

typedef uint8_t* buf_t;

class cppip_stats {
private:
	unsigned frame_count;
	unsigned eth_count;
	unsigned ieee802_2_count;
	unsigned arp_count;
	unsigned rarp_count;
	unsigned ipv4_count;
	unsigned ipv6_count;

public:
	cppip_stats();
	unsigned get_frame_count();
	void set_frame_count(unsigned frame_count);
	void inc_frame_count();
	unsigned get_eth_count();
	void set_eth_count(unsigned eth_count);
	void inc_eth_count();
	unsigned get_ieee802_2_count();
	void set_ieee802_2_count(unsigned ieee802_2_count);
	void inc_ieee802_2_count();
	unsigned get_arp_count();
	void set_arp_count(unsigned arp_count);
	void inc_arp_count();
	unsigned get_rarp_count();
	void set_rarp_count(unsigned rarp_count);
	void inc_rarp_count();
	unsigned get_ipv4_count();
	void set_ipv4_count(unsigned ipv4_count);
	void inc_ipv4_count();
	unsigned get_ipv6_count();
	void set_ipv6_count(unsigned ipv6_count);
	void inc_ipv6_count();
};

extern bool dump_enabled;
extern class cppip_stats stats;

#include "arp.h"
#include "ethertype.h"
#include "eth.h"
#include "ieee802_2.h"
#include "ipproto.h"
#include "ipv4.h"
#include "ipv6.h"
#include "icmpv6.h"
#include "udp.h"

void bufdump(uint8_t* buf, unsigned len);
void dump_ethertype(uint16_t ethertype);
void dump_ethaddr(uint8_t* ethaddr);
void dump_ipproto(uint8_t proto);
void dump_ipaddr(uint32_t ipaddr);
void dump_ipv6addr(uint8_t* ipv6addr);

uint16_t reverse_byte_order_short(uint16_t x);
uint32_t reverse_byte_order_long(uint32_t x);

#endif
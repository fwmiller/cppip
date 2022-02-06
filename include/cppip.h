#ifndef __CPPIP
#define __CPPIP

#include <stdint.h>

#define WINDOWS_IGNORE_PACKING_MISMATCH

static const unsigned ETH_ADDR_LEN = 6;
static const unsigned IPV4_ADDR_LEN = 4;

typedef uint8_t *buf_t;

extern bool dump_enabled;

#include "arp.h"
#include "ethertype.h"
#include "eth.h"
#include "ieee802_2.h"
#include "ipproto.h"
#include "ipv4.h"
#include "ipv6.h"
#include "icmpv6.h"
#include "udp.h"

void bufdump(uint8_t * buf, unsigned len);
void dump_ethertype(uint16_t ethertype);
void dump_ethaddr(uint8_t * ethaddr);
void dump_ipproto(uint8_t proto);
void dump_ipaddr(uint32_t ipaddr);
void dump_ipv6addr(uint8_t * ipv6addr);

uint16_t reverse_byte_order_short(uint16_t x);
uint32_t reverse_byte_order_long(uint32_t x);

#endif

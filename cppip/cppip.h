#ifndef __CPPIP
#define __CPPIP

#include <stdint.h>

#define WINDOWS_IGNORE_PACKING_MISMATCH

static const unsigned ETH_ADDR_LEN = 6;
static const unsigned IPV4_ADDR_LEN = 4;

typedef uint8_t* buf_t;

#include "arp.h"
#include "ethertype.h"
#include "eth.h"
#include "ieee802_2.h"
#include "ipv4.h"
#include "udp.h"

void bufdump(uint8_t* buf, unsigned len);
void dump_ethertype(uint16_t ethertype);
void dump_ethaddr(uint8_t* ethaddr);
void dump_ipaddr(uint32_t ipaddr);

uint16_t net_to_host_order_short(uint16_t x);
uint32_t net_to_host_order_long (uint32_t x);

#endif
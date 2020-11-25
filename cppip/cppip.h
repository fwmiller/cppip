#ifndef __CPPIP
#define __CPPIP

#include <stdint.h>

static const unsigned ETH_ADDR_LEN = 6;

typedef uint8_t* buf_t;

#include "arp.h"
#include "ethertype.h"
#include "eth.h"
#include "ipv4.h"
#include "udp.h"

void bufdump(uint8_t* buf, int len);
void dump_ipaddr(uint32_t ipaddr);
void dump_ethertype(uint16_t ethertype);
void dump_ethaddr(uint8_t* ethaddr);

uint16_t ntohs(uint16_t x);
uint32_t ntohl(uint32_t x);

#endif
#ifndef __CPPIP
#define __CPPIP

#include <stdint.h>

typedef uint8_t* buf_t;

#include "ethertype.h"
#include "eth.h"
#include "ipv4.h"
#include "udp.h"

void bufdump(uint8_t* buf, int len);
uint16_t ntohs(uint16_t x);
uint32_t ntohl(uint32_t x);

#endif
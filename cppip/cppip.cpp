#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include "cppip.h"

static const int LEN = 16;

void
bufdump(uint8_t* buf, int len)
{
	uint8_t* line;
	int i, j, lines;

	lines = (len + LEN - 1) / LEN;
	for (i = 0; i < lines; i++) {
		line = (uint8_t*)buf + i * LEN;
		for (j = 0; j < LEN; j++) {
			printf("%02x ", line[j]);
			if (j == (LEN / 2) - 1)
				printf(" ");
		}
		printf(" ");
		for (j = 0; j < LEN; j++) {
			if (isprint(line[j]))
				printf("%c", (char)line[j]);
			else
				printf(".");
			if (j == (LEN / 2) - 1)
				printf(" ");
		}
		printf("\r\n");
	}
}

void
dump_ipaddr(uint32_t ipaddr)
{
	uint8_t x;

	x = ipaddr >> 24;
	printf("%u.", x);
	x = (ipaddr >> 16) & 0xff;
	printf("%u.", x);
	x = (ipaddr >> 8) & 0xff;
	printf("%u.", x);
	x = ipaddr & 0xff;
	printf("%u", x);
}

void
dump_ethertype(uint16_t ethertype)
{
	switch (ethertype) {
	case ETHERTYPE_IPV4:
		printf("IPv4");
		break;
	case ETHERTYPE_ARP:
		printf("ARP");
		break;
	case ETHERTYPE_RARP:
		printf("RARP");
		break;
	case ETHERTYPE_VLAN:
		printf("802.1Q VLAN");
		break;
	case ETHERTYPE_IPV6:
		printf("IPv6");
		break;
	default:
		printf("UNKNOWN");
	}
}

void
dump_ethaddr(uint8_t* ethaddr)
{
	if (ethaddr == nullptr)
		return;

	printf("%02x:%02x:%02x:%02x:%02x:%02x",
		ethaddr[0], ethaddr[1], ethaddr[2], ethaddr[3], ethaddr[4], ethaddr[5]);
}

uint16_t
ntohs(uint16_t x)
{
	return ((x & 0xff) << 8) |
		((x & 0xff00) >> 8);
}

uint32_t
ntohl(uint32_t x)
{
	return ((x & 0xff) << 24) |
		((x & 0xff00) << 8) |
		((x & 0xff0000) >> 8) |
		((x & 0xff000000) >> 24);
}
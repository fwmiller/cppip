#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include "cppip.h"

static const int LEN = 16;

bool dump_enabled = false;
class cppip_stats stats;

cppip_stats::cppip_stats()
{
	this->frame_count = 0;
}

unsigned
cppip_stats::get_frame_count()
{
	return this->frame_count;
}

void
cppip_stats::set_frame_count(unsigned frame_count)
{
	this->frame_count = frame_count;
}

void
cppip_stats::inc_frame_count()
{
	this->frame_count++;
}

unsigned
cppip_stats::get_eth_count()
{
	return this->eth_count;
}

void
cppip_stats::set_eth_count(unsigned eth_count)
{
	this->eth_count = eth_count;
}

void
cppip_stats::inc_eth_count()
{
	this->eth_count++;
}

unsigned
cppip_stats::get_ieee802_2_count()
{
	return this->ieee802_2_count;
}

void
cppip_stats::set_ieee802_2_count(unsigned ieee802_2_count)
{
	this->ieee802_2_count = ieee802_2_count;
}

void
cppip_stats::inc_ieee802_2_count()
{
	this->ieee802_2_count++;
}

unsigned
cppip_stats::get_arp_count()
{
	return this->arp_count;
}

void
cppip_stats::set_arp_count(unsigned arp_count)
{
	this->arp_count = arp_count;
}

void
cppip_stats::inc_arp_count()
{
	this->arp_count++;
}

unsigned
cppip_stats::get_rarp_count()
{
	return this->rarp_count;
}

void
cppip_stats::set_rarp_count(unsigned rarp_count)
{
	this->rarp_count = rarp_count;
}

void
cppip_stats::inc_rarp_count()
{
	this->rarp_count++;
}

unsigned
cppip_stats::get_ipv4_count()
{
	return this->ipv4_count;
}

void
cppip_stats::set_ipv4_count(unsigned ipv4_count)
{
	this->ipv4_count = ipv4_count;
}

void
cppip_stats::inc_ipv4_count()
{
	this->ipv4_count++;
}

unsigned
cppip_stats::get_ipv6_count()
{
	return this->ipv6_count;
}

void
cppip_stats::set_ipv6_count(unsigned ipv6_count)
{
	this->ipv6_count = ipv6_count;
}

void
cppip_stats::inc_ipv6_count()
{
	this->ipv6_count++;
}

void
bufdump(uint8_t* buf, unsigned len)
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
dump_ethertype(uint16_t ethertype)
{
	switch (ethertype) {
	case ETHERTYPE_IPV4: printf("IPv4"); break;
	case ETHERTYPE_ARP: printf("ARP"); break;
	case ETHERTYPE_RARP: printf("RARP"); break;
	case ETHERTYPE_VLAN: printf("802.1Q VLAN"); break;
	case ETHERTYPE_SNMP: printf("SNMP"); break;
	case ETHERTYPE_IPV6: printf("IPv6"); break;
	case ETHERTYPE_MPLS: printf("MPLS"); break;
	case ETHERTYPE_MPLS_MULTICAST: printf("MPLS Multicast"); break;
	case ETHERTYPE_JUMBO: printf("JUMBO"); break;
	case ETHERTYPE_802_1X: printf("802.1X"); break;
	case ETHERTYPE_802_1AE: printf("802.1AE"); break;
	case ETHERTYPE_PTP: printf("PTP"); break;
	default: printf("UNKNOWN"); break;
	}
}

void
dump_ethaddr(uint8_t* ethaddr)
{
	if (ethaddr == nullptr)
		return;

	printf("%02x:%02x:%02x:%02x:%02x:%02x",
		ethaddr[0], ethaddr[1], ethaddr[2],
		ethaddr[3], ethaddr[4], ethaddr[5]);
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
dump_ipv6addr(uint8_t* ipv6addr)
{
	printf("%02x", ipv6addr[0]);
	for (int i = 1; i < 16; i++) {
		if (i % 2 == 0)
			printf(":");
		printf("%02x", ipv6addr[i]);
	}
}

uint16_t
reverse_byte_order_short(uint16_t x)
{
	return (((x & 0xff) << 8) | ((x & 0xff00) >> 8));
}

uint32_t
reverse_byte_order_long(uint32_t x)
{
	return (((x & 0xff) << 24) |
		((x & 0xff00) << 8) |
		((x & 0xff0000) >> 8) |
		((x & 0xff000000) >> 24));
}
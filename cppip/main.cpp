#include <stdio.h>
#include "cppip.h"

/*
uint8_t pkt[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x08, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0a, 0x20, 0x3f, 0xc0, 0x0a, 0x20, 0x3c,
                  0x01, 0x0a, 0x00, 0x3c, 0x00, 0x10, 0x00, 0x00 };
*/

#include "traces/arp.c"
//#include "traces/rarp_req_reply.c"
//#include "traces/sip-rtp-g711.c"

int main()
{
    class arp arp;
    class eth eth;
    class ipv4 ip;
    class udp udp;

    printf("C++ Internet Protocols\r\n");

    bufdump((uint8_t *)pkt1, sizeof(pkt1));
    eth.set_buf((uint8_t*)pkt1);
    eth.dump();

    switch (eth.get_ethertype()) {
    case ETHERTYPE_IPV4:
        ip.set_buf(eth.get_buf() + sizeof(struct eth_hdr));
        ip.dump();
        udp.set_buf(ip.get_buf() + sizeof(struct ipv4_hdr));
        udp.dump();
        break;
    case ETHERTYPE_ARP:
        arp.set_buf(eth.get_buf() + sizeof(struct eth_hdr));
        arp.dump();
        break;
    case ETHERTYPE_RARP:
        arp.set_buf(eth.get_buf() + sizeof(struct eth_hdr));
        arp.dump();
        break;
    }
}
#include <stdio.h>
#include "cppip.h"

/*
uint8_t pkt[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x08, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0a, 0x20, 0x3f, 0xc0, 0x0a, 0x20, 0x3c,
                  0x01, 0x0a, 0x00, 0x3c, 0x00, 0x10, 0x00, 0x00 };
*/

//#include "traces/arp.c"
//#include "traces/rarp_req_reply.c"
#include "traces/sip-rtp-g711.c"

int main()
{
    class eth eth;

    printf("C++ Internet Protocols (cppip)\r\n");

    bufdump((uint8_t *)pkt1, sizeof(pkt1));
    eth.set_buf((uint8_t*)pkt1);
    eth.dump();
    eth.receive();
}
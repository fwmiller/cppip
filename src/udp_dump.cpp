#include <stdio.h>
#include "cppip.h"

void udp::dump() {
    if (this->buf == nullptr) return;

    udp_hdr_t uh = (udp_hdr_t)this->buf;

    printf("udp dst %u src %u len %u cksum 0x%04x\r\n",
           reverse_byte_order_short(uh->dst),
           reverse_byte_order_short(uh->src),
           reverse_byte_order_short(uh->len),
           reverse_byte_order_short(uh->cksum));
    // bufdump(this->buf + sizeof(struct udp_hdr),
    // reverse_byte_order_short(uh->len));
}

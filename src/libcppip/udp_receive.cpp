#include <stdio.h>
#include <stdlib.h>
#include "udp.h"
#include "udptab.h"

void
udp::receive() {
    if (this->buf == NULL)
        return;

    udp_hdr_t uh = (udp_hdr_t) this->buf;
    uint16_t port = reverse_byte_order_short(uh->dst);

    class bufq *q = udptab.find_port(port);
    if (q == NULL) {
        // No input queue open drop packet data

        // TODO: for fun - just allocating a UDP queue for any incoming
        // UDP packet until the UDP table is filled up...
        q = udptab.alloc_port(port);
        if (q == NULL)
            return;
    }
    int len = reverse_byte_order_short(uh->len);
    q->append(this->buf + sizeof(struct udp_hdr), len);

    printf("udp port %u rcvd %d bytes\r\n", port, len);
    // q->dump_contents();
    // printf("\r\n");
}

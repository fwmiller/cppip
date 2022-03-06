#include "udp.h"
#include <stdio.h>
#include <stdlib.h>
#include "udptab.h"

udp::udp() {
    this->buf = NULL;
}

buf_t
udp::get_buf() {
    return this->buf;
}

void
udp::set_buf(buf_t buf) {
    this->buf = buf;
}

void
udp::receive() {
    if (this->buf == NULL)
        return;

    udp_hdr_t uh = (udp_hdr_t) this->buf;
    class inq *q = udptab.find_port(reverse_byte_order_short(uh->dst));
    if (q == NULL) {
        // No input queue open drop packet data
        return;
    }
    int len = reverse_byte_order_short(uh->len);
    int n = q->append(this->buf + sizeof(struct udp_hdr), len);
    printf("rcvd %d bytes queued %d bytes\r\n", len, n);
}

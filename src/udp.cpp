#include <stdio.h>
#include <stdlib.h>
#include "cppip.h"
#include "inq.h"

static const int RECV_PORTS = 16;

static class inq udptab[RECV_PORTS];

static class inq *udptab_find(uint16_t port) {
    for (int i = 0; i < RECV_PORTS; i++)
        if (udptab[i].get_port() == port) return &(udptab[i]);
    return NULL;
}

udp::udp() {
    this->port = 0;
    this->buf = NULL;
}

uint16_t udp::get_port() { return this->port; }

void udp::set_port(uint16_t port) { this->port = port; }

buf_t udp::get_buf() { return this->buf; }

void udp::set_buf(buf_t buf) { this->buf = buf; }

void udp::receive() {
    if (this->buf == NULL) return;

    udp_hdr_t uh = (udp_hdr_t)this->buf;
    class inq *q = udptab_find(reverse_byte_order_short(uh->dst));
    if (q == NULL) {
        // No input queue open drop packet data
        return;
    }
    int len = reverse_byte_order_short(uh->len);
    int n = q->append(this->buf + sizeof(struct udp_hdr), len);
    printf("rcvd %d bytes queued %d bytes\r\n", len, n);
}

int udp::read(buf_t buf, int len) {
    if (this->port == 0) return (-1);

    class inq *q = udptab_find(this->port);
    if (q == NULL) {
        // No input queue
        return (-1);
    }
    return q->remove(buf, len);
}

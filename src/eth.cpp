#include "cppip.h"
#include "stats.h"

eth::eth() {
    this->buf = nullptr;
    this->buflen = 0;
}

uint16_t eth::get_ethertype() {
    if (this->buf == nullptr) return 0;

    eth_hdr_t eh = (eth_hdr_t)this->buf;
    return reverse_byte_order_short(eh->ethertype);
}

buf_t eth::get_buf() { return this->buf; }

void eth::set_buf(buf_t buf) { this->buf = buf; }

unsigned eth::get_buflen() { return this->buflen; }

void eth::set_buflen(unsigned buflen) { this->buflen = buflen; }

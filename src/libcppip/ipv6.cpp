#include <stdio.h>
#include <stdlib.h>
#include "cppip.h"

ipv6::ipv6() {
    this->hdr = NULL;
}

buf_t
ipv6::get_hdr() {
    return this->hdr;
}

void
ipv6::set_hdr(buf_t hdr) {
    this->hdr = hdr;
}

void
ipv6::receive() {
    if (this->hdr == NULL)
        return;

    ipv6_hdr_t ih = (ipv6_hdr_t) this->hdr;

    switch (ih->next) {
    case IP_PROTO_IPV6_ICMP: {
        class icmpv6 ic;
        ic.set_buf(this->hdr + sizeof(struct ipv6_hdr));
        if (dump_enabled)
            ic.dump();
        ic.receive();
    } break;
    }
}

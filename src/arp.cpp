#include <stdlib.h>
#include <string.h>
#include "arptab.h"
#include "cppip.h"

extern class arptab_entry *my_addr;

arp::arp() { this->buf = NULL; }

buf_t arp::get_buf() { return this->buf; }

void arp::set_buf(buf_t buf) { this->buf = buf; }

void arp::receive() {
    if (this->buf == NULL) return;

    arp_hdr_t ah = (arp_hdr_t)this->buf;

    switch (reverse_byte_order_short(ah->opcode)) {
        case ARP_OP_REQ:
            break;
        case ARP_OP_REP:
            break;
    }
}

void arp::generate(uint8_t *buf, uint16_t hw, uint16_t proto,
                   uint8_t hw_addr_len, uint8_t proto_addr_len,
                   uint16_t opcode, uint8_t *sha, uint32_t spa, uint8_t *tha,
                   uint32_t tpa) {
    arp_hdr_t ah = (arp_hdr_t)buf;
    ah->hw = reverse_byte_order_short(hw);
    ah->proto = reverse_byte_order_short(proto);
    ah->hw_addr_len = hw_addr_len;
    ah->proto_addr_len = proto_addr_len;
    ah->opcode = reverse_byte_order_short(opcode);
    if (sha != NULL) memcpy(ah->sha, sha, ETH_ADDR_LEN);
    ah->spa = spa;
    if (tha != NULL) memcpy(ah->tha, tha, ETH_ADDR_LEN);
    ah->tpa = tpa;
}

static void gen_arp_packet(uint8_t *buf, uint16_t opcode, uint8_t *sha,
                           uint32_t spa, uint8_t *tha, uint32_t tpa) {
    arp_hdr_t ah = (arp_hdr_t)(buf + sizeof(struct eth_hdr));
    ah->hw = reverse_byte_order_short(ARP_HW_ETH);
    ah->proto = reverse_byte_order_short(ETHERTYPE_ARP);
    ah->hw_addr_len = ETH_ADDR_LEN;
    ah->proto_addr_len = IPV4_ADDR_LEN;
    ah->opcode = reverse_byte_order_short(opcode);
    if (sha != NULL) memcpy(ah->sha, sha, ETH_ADDR_LEN);
    ah->spa = spa;
    if (tha != NULL) memcpy(ah->tha, tha, ETH_ADDR_LEN);
    ah->tpa = tpa;
}

void arp::send_probe() {
    // Generate ARP probe packet
    uint8_t buf[ETH_MTU_SIZE];
    memset(buf, 0, ETH_MTU_SIZE);  // Zeros ah->tha

    // Leave space for the Ethernet header
    gen_arp_packet(buf + sizeof(struct eth_hdr), ARP_OP_REQ,
                   my_addr->get_ha(), 0, NULL, 0);

    // Format Ethernet header
    eth_hdr_t eh = (eth_hdr_t)buf;
    memset(&(eh->dst), 0xff, ETH_ADDR_LEN);
    memcpy(&(eh->src), my_addr->get_ha(), ETH_ADDR_LEN);
    eh->ethertype = reverse_byte_order_short(ETHERTYPE_ARP);

    class eth e;
    e.set_buf(buf);
    e.set_buflen(sizeof(struct arp_hdr) + sizeof(struct eth_hdr));
    e.send();
}

void arp::send_announce() {
    // Generate ARP REQ announcement packet
    //  Note: ARP REP announcement method not supported
    uint8_t buf[ETH_MTU_SIZE];
    memset(buf, 0, ETH_MTU_SIZE);  // Zeros ah->tha
    gen_arp_packet(buf + sizeof(struct eth_hdr), ARP_OP_REQ,
                   my_addr->get_ha(),
                   reverse_byte_order_short(my_addr->get_pa()), NULL,
                   reverse_byte_order_short(my_addr->get_pa()));
}

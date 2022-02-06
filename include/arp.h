#ifndef __ARP_H
#define __ARP_H

#include "cppip.h"

const static uint16_t ARP_HW_ETH = 0x0001;
const static uint16_t ARP_HW_802 = 0x0006;
const static uint16_t ARP_HW_SER = 0x0014;

const static uint16_t ARP_OP_REQ = 0x0001;
const static uint16_t ARP_OP_REP = 0x0002;
const static uint16_t RARP_OP_REQ = 0x0003;
const static uint16_t RARP_OP_REP = 0x0004;

struct arp_hdr {
    uint16_t hw;
    uint16_t proto;
    uint8_t hw_addr_len;
    uint8_t proto_addr_len;
    uint16_t opcode;
    uint8_t sha[ETH_ADDR_LEN];
    uint32_t spa;
    uint8_t tha[ETH_ADDR_LEN];
    uint32_t tpa;
} __attribute__((packed));

typedef struct arp_hdr *arp_hdr_t;

class arp {
   private:
    buf_t buf;

   public:
    arp();
    buf_t get_buf();
    void set_buf(buf_t buf);
    void receive();
    void dump();
    void send_probe();
    void send_announce();
};

static const int ARPTAB_ENTRIES = 16;

class arptab_entry {
   private:
    uint8_t ha[ETH_ADDR_LEN];  // Hardware address (Ethernet)
    uint32_t pa;               // Protocol address (IPv4)

   public:
    arptab_entry();
    uint8_t *get_ha();
    void set_ha(uint8_t *ha);
    uint32_t get_pa();
    void set_pa(uint32_t pa);
};

#endif

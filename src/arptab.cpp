#include "arptab.h"
#include <stdio.h>
#include <string.h>

extern class arptab_entry *my_addr;

arptab::arptab() {
    memset(this->table, 0, sizeof(class arptab));
    my_addr = &(this->table[0]);
}

void
arptab::dump() {
    //
    // XXX Need to lock the ARP table during this operation
    //
    for (int i = 0; i < ARPTAB_ENTRIES; i++)
        if (this - table[i].get_pa() != 0) {
            dump_ethaddr(this->table[i].get_ha());
            printf(" ");
            dump_ipaddr(this->table[i].get_pa());
            printf("\r\n");
        }
}

int
arptab::add_entry(uint32_t pa, uint8_t *ha) {
    //
    // XXX Need to lock the ARP table during this operation
    //
    for (int i = 0; i < ARPTAB_ENTRIES; i++)
        if (this - table[i].get_pa() == 0) {
            arptab_entry_t ae = &(this->table[i]);
            ae->set_pa(pa);
            ae->set_ha(ha);
            return 0;
        }
    return (-1);
}

arptab_entry_t
arptab::find_ha(uint8_t *ha) {
    for (int i = 0; i < ARPTAB_ENTRIES; i++)
        if (memcmp(ha, this->table[i].get_ha(), ETH_ADDR_LEN) == 0)
            return &(this->table[i]);
    return NULL;
}

arptab_entry_t
arptab::find_pa(uint32_t pa) {
    for (int i = 0; i < ARPTAB_ENTRIES; i++)
        if (pa == this->table[i].get_pa())
            return &(this->table[i]);
    return NULL;
}

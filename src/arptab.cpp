#include "arptab.h"
#include <stdlib.h>
#include <string.h>
#include "cppip.h"

extern class arptab_entry *my_addr;

arptab_entry::arptab_entry() {
    memset(this->ha, 0, ETH_ADDR_LEN);
    this->pa = 0;
}

uint8_t *arptab_entry::get_ha() { return this->ha; }

void arptab_entry::set_ha(uint8_t *ha) { memcpy(this->ha, ha, ETH_ADDR_LEN); }

uint32_t arptab_entry::get_pa() { return this->pa; }

void arptab_entry::set_pa(uint32_t pa) { this->pa = pa; }

arptab::arptab() {
    memset(this->table, 0, sizeof(class arptab));
    my_addr = &(table[0]);
}

arptab_entry_t arptab::find_ha(uint8_t *ha) {
    for (int i = 0; i < ARPTAB_ENTRIES; i++)
        if (memcmp(ha, this->table[i].get_ha(), ETH_ADDR_LEN) == 0)
            return &(this->table[i]);
    return NULL;
}

arptab_entry_t arptab::find_pa(uint32_t pa) {
    for (int i = 0; i < ARPTAB_ENTRIES; i++)
        if (pa == this->table[i].get_pa()) return &(this->table[i]);
    return NULL;
}

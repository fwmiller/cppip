#include <stdlib.h>
#include <string.h>
#include "cppip.h"

static class arptab_entry arptab[ARPTAB_ENTRIES];

class arptab_entry *my_addr = NULL;

void arptab_init() {
    memset(arptab, 0, sizeof(arptab));
    my_addr = &(arptab[0]);
}

static class arptab_entry *arptab_find_ha(uint8_t *ha) {
    for (int i = 0; i < ARPTAB_ENTRIES; i++)
        if (memcmp(ha, arptab[i].get_ha(), ETH_ADDR_LEN) == 0)
            return &(arptab[i]);
    return NULL;
}

static class arptab_entry *arptab_find_pa(uint32_t pa) {
    for (int i = 0; i < ARPTAB_ENTRIES; i++)
        if (pa == arptab[i].get_pa()) return &(arptab[i]);
    return NULL;
}

arptab_entry::arptab_entry() {
    memset(this->ha, 0, ETH_ADDR_LEN);
    this->pa = 0;
}

uint8_t *arptab_entry::get_ha() { return this->ha; }

void arptab_entry::set_ha(uint8_t *ha) { memcpy(this->ha, ha, ETH_ADDR_LEN); }

uint32_t arptab_entry::get_pa() { return this->pa; }

void arptab_entry::set_pa(uint32_t pa) { this->pa = pa; }

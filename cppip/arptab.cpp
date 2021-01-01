#include <string.h>
#include "cppip.h"

static const int ARPTAB_ENTRIES = 16;

class arptab_entry {
private:
	uint8_t ha[ETH_ADDR_LEN];	// Hardware address (Ethernet)
	uint32_t pa;				// Protocol address (IPv4)

public:
	arptab_entry();
	uint8_t* get_ha();
	void set_ha(uint8_t* ha);
	uint32_t get_pa();
	void set_pa(uint32_t pa);
};

static class arptab_entry arptab[ARPTAB_ENTRIES];

static class arptab_entry*
arptab_find_ha(uint8_t* ha)
{
	for (int i = 0; i < ARPTAB_ENTRIES; i++)
		if (memcmp(ha, arptab[i].get_ha(), ETH_ADDR_LEN) == 0)
			return &(arptab[i]);
	return nullptr;
}

static class arptab_entry*
arptab_find_pa(uint32_t pa)
{
	for (int i = 0; i < ARPTAB_ENTRIES; i++)
		if (pa == arptab[i].get_pa())
			return &(arptab[i]);
	return nullptr;
}

arptab_entry::arptab_entry()
{
	memset(this->ha, 0, ETH_ADDR_LEN);
	this->pa = 0;
}

uint8_t*
arptab_entry::get_ha()
{
	return this->ha;
}

void
arptab_entry::set_ha(uint8_t* ha)
{
	memcpy(this->ha, ha, ETH_ADDR_LEN);
}

uint32_t
arptab_entry::get_pa()
{
	return this->pa;
}

void
arptab_entry::set_pa(uint32_t pa)
{
	this->pa = pa;
}
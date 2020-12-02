#ifndef __IEEE_802_3_H
#define __IEEE_802_3_H

#include <stdint.h>
#include "cppip.h"

#pragma pack(1)
struct ieee802_2_hdr {
	uint8_t dsap;
	uint8_t ssap;
	uint8_t control;
	uint8_t ext_control;
};

typedef struct ieee802_2_hdr* ieee802_2_hdr_t;

class ieee802_2 {
private:
	buf_t buf;
public:
	ieee802_2();
	buf_t get_buf();
	void set_buf(buf_t buf);
	void receive();
	void dump();
};

#endif
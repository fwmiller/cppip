#ifndef __IEEE_802_3_H
#define __IEEE_802_3_H

#include <stdint.h>
#include "cppip.h"

#pragma pack(1)
struct ieee802_3_hdr {

};

typedef struct ieee802_3_hdr* ieee802_3_hdr_t;

class ieee802_3 {
private:
	buf_t buf;
public:
	ieee802_3();
	buf_t get_buf();
	void set_buf(buf_t buf);
	void receive();
	void dump();
};

#endif
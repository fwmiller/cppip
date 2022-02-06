#ifndef __INQ_H
#define __INQ_H

#include "cppip.h"

//static const int MAX_INQ_SIZE = 2048; // 2 KB
static const int MAX_INQ_SIZE = 16;	// 16 bytes

class inq {
 private:
	uint16_t port;
	uint8_t q[MAX_INQ_SIZE];
	int h, t;
	bool full;

 public:
	 inq();
	uint16_t get_port();
	void set_port(uint16_t port);
	int append(buf_t buf, int len);
	int remove(buf_t buf, int len);
	void dump();
};

#endif

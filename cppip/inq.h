#pragma once

#include "cppip.h"

//static const int MAX_INQ_SIZE = 2048; // 2 KB
static const int MAX_INQ_SIZE = 5;

class inq {
private:
	uint8_t q[MAX_INQ_SIZE];
	int h, t;
	bool full;

public:
	inq();
	int append(buf_t buf, int len);
	int remove(buf_t buf, int len);
	void dump();
};
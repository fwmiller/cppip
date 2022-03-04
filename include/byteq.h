#ifndef __BYTEQ_H
#define __BYTEQ_H

#include "cppip.h"

// static const int MAX_BYTEQ_SIZE = 2048; // 2 KB
static const int MAX_BYTEQ_SIZE = 16;  // 16 bytes

class byteq {
private:
    uint8_t q[MAX_BYTEQ_SIZE];
    int len;
    int h, t;
    bool full;

public:
    byteq();
    int get_length();
    virtual int append(buf_t buf, int len);
    virtual int remove(buf_t buf, int len);
    virtual void dump();
    virtual void dump_contents();
};

#endif

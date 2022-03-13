#ifndef __BUF_H
#define __BUF_H

#include <stdint.h>

static const int BUFSIZE = 2048;      // bytes
static const int BUFPOOL_SIZE = 512;  // buffers

typedef uint8_t *buf_t;

class bufpool {
private:
    buf_t pool[BUFPOOL_SIZE * BUFSIZE];
    int idx;

public:
    bufpool();
    buf_t alloc();
};

#endif

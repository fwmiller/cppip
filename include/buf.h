#ifndef __BUF_H
#define __BUF_H

#include <stdint.h>

typedef uint8_t *buf_t;

class bufpool {
private:
    buf_t pool;
    int nbufs;
    int bufsize;
    int idx;

public:
    bufpool(int nbufs, int bufsize);
    int get_nbufs();
    int get_bufsize();
    buf_t alloc();
};

class bufq {
private:
    buf_t *q;
    int *len;
    int entries;
    int h, t;
    bool full;

public:
    bufq(int entries);
    int get_length();
    int append(buf_t buf);
    buf_t remove();
    void dump();
    void dump_contents();
};

#endif

#ifndef __BUF_H
#define __BUF_H

#include <stdint.h>

typedef uint8_t *buf_t;

class bufpool {
private:
    buf_t pool;
    int nbufs;
    int bufsize;
    buf_t stack;

public:
    bufpool(int nbufs, int bufsize);
    int get_nbufs();
    int get_bufsize();
    buf_t pop();
    void push(buf_t buf);
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
    int append(buf_t buf, int len);
    buf_t remove(int *len);
    void dump();
    void dump_contents();
};

#endif

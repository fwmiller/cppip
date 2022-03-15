#include <stdlib.h>
#include <string.h>
#include "buf.h"

bufpool::bufpool(int nbufs, int bufsize) {
    this->pool = (buf_t) malloc(nbufs * bufsize);
    this->nbufs = nbufs;
    this->bufsize = bufsize;
    this->idx = 0;
}

int
bufpool::get_nbufs() {
    return this->nbufs;
}

int
bufpool::get_bufsize() {
    return this->bufsize;
}

buf_t
bufpool::alloc() {
    if (this->idx == this->nbufs)
        return NULL;
    return (buf_t)(this->pool + ((this->idx++) * this->bufsize));
}

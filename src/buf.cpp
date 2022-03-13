#include "buf.h"
#include <stdlib.h>
#include <string.h>

bufpool::bufpool() {
    memset(this->pool, 0, BUFPOOL_SIZE * BUFSIZE);
    this->idx = 0;
}

buf_t
bufpool::alloc() {
    if (this->idx == BUFPOOL_SIZE)
        return NULL;
    return (buf_t)(this->pool + ((this->idx++) * BUFSIZE));
}

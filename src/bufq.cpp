#include <stdlib.h>
#include <string.h>
#include "buf.h"

//
// A byteq is a First-In-First-Out (FIFO) queue of buf_t pointers. The
// data structure works with buf_t pointers, it does not copy data in
// out of the buffers
//

bufq::bufq(int entries) {
    int qsize = entries * sizeof(void *);
    this->q = (buf_t *) malloc(qsize);
    memset(this->q, 0, qsize);

    int lensize = entries * sizeof(int);
    this->len = (int *) malloc(lensize);
    memset(this->len, 0, lensize);

    this->entries = entries;
    this->h = 0;
    this->t = 0;
    this->full = false;
}

//
// Append a buf_t pointer to the tail of the queue
//
int
bufq::append(buf_t buf, int len) {
    if (this->full)
        return (-1);

    this->q[t] = buf;
    this->len[t] = len;
    this->t = (this->t + 1) % this->entries;
    if (this->t == this->h)
        this->full = true;

    return 0;
}

//
// Remove a buf_t pointer from the head of the queue
//
buf_t
bufq::remove(int *len) {
    if (!full && this->h == this->t) {
        *len = 0;
        return NULL;
    }
    buf_t buf = this->q[this->h];
    *len = this->len[this->h];
    this->h = (this->h + 1) % this->entries;
    if (this->full)
        this->full = false;

    return buf;
}

void
bufq::dump() {
    return;
}

void
bufq::dump_contents() {
    return;
}

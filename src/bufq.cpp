#include <stdlib.h>
#include <string.h>
#include "buf.h"

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

int
bufq::get_length() {
    return 0;
}

int
bufq::append(buf_t buf) {
    if (this->full)
        return (-1);

    this->q[h] = buf;
    this->h = (this->h + 1) % this->entries;
    if (this->h == this->t)
        this->full = true;

    return 0;
}

buf_t
bufq::remove() {
    return NULL;
}

void
bufq::dump() {
    return;
}

void
bufq::dump_contents() {
    return;
}

#include <stdlib.h>
#include <string.h>
#include "buf.h"

bufq::bufq(int entries) {
    this->q = (buf_t *) malloc(entries * sizeof(void *));
    memset(this->q, 0, entries * sizeof(void *));
    this->len = 0;
    this->h = 0;
    this->t = 0;
    this->full = false;
}

int
bufq::get_length() {
    return this->len;
}

int
bufq::append(buf_t buf) {
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

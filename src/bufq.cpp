#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buf.h"

//
// A byteq is a First-In-First-Out (FIFO) queue of buf_t pointers. The
// data structure works with buf_t pointers, it does not copy data in
// out of the buffers
//

bufq::bufq(int entries) {
    int size = entries * sizeof(void *);
    this->q = (buf_t *) malloc(size);
    memset(this->q, 0, size);

    size = entries * sizeof(int);
    this->size = (int *) malloc(size);
    this->len = (int *) malloc(size);
    memset(this->size, 0, size);
    memset(this->len, 0, size);

    this->entries = entries;
    this->h = 0;
    this->t = 0;
    this->full = false;
}

//
// Determine how many buffers are currently in the queue
//
int
bufq::get_length() {
    int h, len;

    if (this->full)
        return this->entries;

    for (len = 0, h = this->h; h != this->t;
         len++, h = (h + 1) % this->entries)
        ;

    return len;
}

//
// Append a buf_t pointer to the tail of the queue
//
int
bufq::append(buf_t buf, int size, int len) {
    if (this->full)
        return (-1);

    this->q[t] = buf;
    this->size[t] = size;
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
bufq::remove(int *size, int *len) {
    if (!(this->full) && this->h == this->t) {
        *len = 0;
        return NULL;
    }
    buf_t buf = this->q[this->h];
    *size = this->size[this->h];
    *len = this->len[this->h];
    this->h = (this->h + 1) % this->entries;
    if (this->full)
        this->full = false;

    return buf;
}

void
bufq::dump() {
    if (!(this->full) && this->h == this->t)
        return;

    for (int i = this->h;;) {
        printf("%p  %5d  %5d\r\n", this->q[i], this->size[i], this->len[i]);

        i = (i + 1) % this->entries;
        if (i == this->t)
            break;
    }
}

void
bufq::dump_contents() {
    if (!(this->full) && this->h == this->t)
        return;

    for (int i = this->h;;) {
        printf("[");
        fflush(stdout);

        for (int j = 0; j < this->len[i]; j++) {
            char ch = *(this->q[i] + j);
            if (isprint(ch)) {
                printf("%c", ch);
                fflush(stdout);
            } else {
                printf(".");
                fflush(stdout);
            }
        }
        printf("]\r\n");
        fflush(stdout);

        i = (i + 1) % this->entries;
        if (i == this->t)
            break;
    }
}

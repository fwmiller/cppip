#include "byteq.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

//
// A byteq is a First-In-First-Out (FIFO) queue with a fixed size
// circular buffer.  Data is copied into during an append() operation
// and copied out during a remove() operation
//

#define CLEAR                           \
    memset(this->q, 0, MAX_BYTEQ_SIZE); \
    this->len = 0;                      \
    this->h = 0;                        \
    this->t = 0;                        \
    this->full = false

byteq::byteq() {
    CLEAR;
}

void
byteq::clear() {
    CLEAR;
}

int
byteq::get_length() {
    return this->len;
}

//
// Append len bytes contained in buf to the tail of the queue
//
int
byteq::append(buf_t buf, int len) {
    if (this->full)
        return 0;

    // Input data contained in buf is copied byte by byte to the
    // tail of the FIFO buffer
    //
    int t = this->t;
    for (int i = 0;;) {
        this->q[t] = buf[i++];
        this->len++;

        t = (t + 1) % MAX_BYTEQ_SIZE;
        if (t == this->h) {
            // Queue buffer has reached capacity
            this->t = t;
            this->full = true;
            return i;
        }
        if (i == len) {
            // All len bytes of buf have been appended
            this->t = t;
            return i;
        }
    }
}

//
// Remove len bytes from the head of the queue and copy them to buf
//
int
byteq::remove(buf_t buf, int len) {
    int h = this->h;
    for (int i = 0;;) {
        if (i == len) {
            // All len bytes requested from the queue have been copied to buf
            this->h = h;
            return i;
        }
        if (h == this->t && !full) {
            // Empty queue
            this->h = h;
            return i;
        }
        // Copy and clear byte from tail of queue to proper location in buf
        buf[i++] = this->q[h];
        this->q[h] = 0;
        this->len--;

        full = false;
        h = (h + 1) % MAX_BYTEQ_SIZE;
    }
}

void
byteq::dump() {
    printf("contains %d bytes\r\n", this->len);
    printf(" ");
    for (int i = 0; i < MAX_BYTEQ_SIZE; i++)
        if (i == this->h)
            printf("h");
        else if (i == this->t)
            printf("t");
        else
            printf(" ");

    printf(" \r\n[");
    for (int i = 0; i < MAX_BYTEQ_SIZE; i++)
        if (isprint(this->q[i]))
            printf("%c", this->q[i]);
        else
            printf(".");

    printf("]\r\n");
}

void
byteq::dump_contents() {
    printf("[");
    fflush(stdout);
    for (int i = 0; i < MAX_BYTEQ_SIZE; i++)
        if (isprint(this->q[i])) {
            printf("%c", this->q[i]);
            fflush(stdout);
        } else {
            printf(".");
            fflush(stdout);
        }

    printf("]");
    fflush(stdout);
}

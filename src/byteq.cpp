#include "byteq.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

byteq::byteq() {
    memset(this->q, 0, MAX_BYTEQ_SIZE);
    this->h = 0;
    this->t = 0;
    this->full = false;
}

int
byteq::append(buf_t buf, int len) {
    if (this->full)
        return 0;

    int h = this->h;
    for (int i = 0;;) {
        this->q[h] = buf[i++];

        h = (h + 1) % MAX_BYTEQ_SIZE;
        if (h == this->t) {
            this->h = h;
            this->full = true;
            return i;
        }
        if (i == len) {
            this->h = h;
            return i;
        }
    }
}

int
byteq::remove(buf_t buf, int len) {
    int t = this->t;
    for (int i = 0;;) {
        if (i == len) {
            this->t = t;
            return i;
        }
        if (t == this->h && !full) {
            this->t = t;
            return i;
        }
        buf[i++] = this->q[t];
        this->q[t] = 0;

        if (full)
            full = false;
        t = (t + 1) % MAX_BYTEQ_SIZE;
    }
}

void
byteq::dump() {
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

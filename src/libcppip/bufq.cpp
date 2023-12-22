#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buf.h"

//
// A bufq is a First-In-First-Out (FIFO) queue of buf_t pointers. The
// data structure works with buf_t pointers, it does not touch the data
// in the buffers
//

bufq::bufq(int entries, int bufsize) {
    int size = entries * sizeof(void *);
    this->q = (buf_t *) malloc(size);
    memset(this->q, 0, size);

    size = entries * sizeof(int);
    this->len = (int *) malloc(size);
    memset(this->len, 0, size);

    this->entries = entries;
    this->bufsize = bufsize;
    this->h = 0;
    this->t = 0;
    this->full = false;

    pthread_mutex_init(&(this->mutex), NULL);
}

//
// Determine number of buffers in the queue
//
int
bufq::get_nbufs() {
    int h, n;

    pthread_mutex_lock(&(this->mutex));
    if (this->full) {
        int entries = this->entries;
        pthread_mutex_unlock(&(this->mutex));
        return entries;
    }
    for (n = 0, h = this->h; h != this->t; n++, h = (h + 1) % this->entries)
        ;

    pthread_mutex_unlock(&(this->mutex));
    return n;
}

int
bufq::get_bufsize() {
    pthread_mutex_lock(&(this->mutex));
    int bufsize = this->bufsize;
    pthread_mutex_unlock(&(this->mutex));
    return bufsize;
}

//
// Determine the sum of the lengths of the buffers in the queue
//
int
bufq::get_length() {
    int h, len;

    pthread_mutex_lock(&(this->mutex));
    if (this->full) {
        int entries = this->entries;
        pthread_mutex_unlock(&(this->mutex));
        return entries;
    }

    for (len = 0, h = this->h; h != this->t;
         len += this->len[h], h = (h + 1) % this->entries)
        ;

    pthread_mutex_unlock(&(this->mutex));
    return len;
}

//
// Append a buf_t pointer to the tail of the queue
//
int
bufq::append(buf_t buf, int len) {
    if (buf == NULL || this->full)
        return (-1);

    pthread_mutex_lock(&(this->mutex));
    this->q[t] = buf;
    this->len[t] = len;
    this->t = (this->t + 1) % this->entries;
    if (this->t == this->h)
        this->full = true;

    pthread_mutex_unlock(&(this->mutex));
    return 0;
}

//
// Remove a buf_t pointer from the head of the queue
//
buf_t
bufq::remove(int *len) {
    pthread_mutex_lock(&(this->mutex));

    if (!(this->full) && this->h == this->t) {
        pthread_mutex_unlock(&(this->mutex));
        *len = 0;
        return NULL;
    }
    buf_t buf = this->q[this->h];
    *len = this->len[this->h];
    this->h = (this->h + 1) % this->entries;
    if (this->full)
        this->full = false;

    pthread_mutex_unlock(&(this->mutex));
    return buf;
}

void
bufq::dump() {
    pthread_mutex_lock(&(this->mutex));

    if (!(this->full) && this->h == this->t) {
        pthread_mutex_unlock(&(this->mutex));
        return;
    }
    printf("<");
    for (int i = this->h;;) {
        printf("%d", this->len[i]);

        i = (i + 1) % this->entries;
        if (i == this->t)
            break;

        printf(",");
    }
    printf(">");

    pthread_mutex_unlock(&(this->mutex));
}

void
bufq::dump_contents() {
    pthread_mutex_lock(&(this->mutex));

    if (!(this->full) && this->h == this->t) {
        pthread_mutex_unlock(&(this->mutex));
        return;
    }

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
    pthread_mutex_unlock(&(this->mutex));
}

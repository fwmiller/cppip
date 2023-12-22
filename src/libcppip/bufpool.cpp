#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buf.h"

bufpool::bufpool(int nbufs, int bufsize) {
    buf_t pool = (buf_t) malloc(nbufs * bufsize);
    memset(pool, 0, nbufs * bufsize);
    this->pool = pool;
    this->nbufs = nbufs;
    this->bufsize = bufsize;
    this->stack = NULL;
    pthread_mutex_init(&(this->mutex), NULL);

    // Setup the stack
    for (int i = 0; i < nbufs; i++)
        this->push((buf_t) (pool + (i * bufsize)));
}

int
bufpool::get_nbufs() {
    pthread_mutex_lock(&(this->mutex));
    int nbufs = this->nbufs;
    pthread_mutex_unlock(&(this->mutex));
    return nbufs;
}

int
bufpool::get_bufsize() {
    pthread_mutex_lock(&(this->mutex));
    int bufsize = this->bufsize;
    pthread_mutex_unlock(&(this->mutex));
    return bufsize;
}

buf_t
bufpool::pop() {
    pthread_mutex_lock(&(this->mutex));
    if (this->stack == NULL) {
        pthread_mutex_unlock(&(this->mutex));
        return NULL;
    }
    buf_t buf = this->stack;
    this->stack = *((buf_t *) this->stack);
    pthread_mutex_unlock(&(this->mutex));
    return buf;
}

void
bufpool::push(buf_t buf) {
    pthread_mutex_lock(&(this->mutex));
    if (buf == NULL) {
        pthread_mutex_unlock(&(this->mutex));
        return;
    }
    *((buf_t *) buf) = this->stack;
    this->stack = buf;
    pthread_mutex_unlock(&(this->mutex));
}

void
bufpool::dump() {
    pthread_mutex_lock(&(this->mutex));
    for (buf_t buf = this->stack; buf != NULL;) {
        printf("%p\r\n", buf);
        buf = *((buf_t *) buf);
    }
    pthread_mutex_unlock(&(this->mutex));
}

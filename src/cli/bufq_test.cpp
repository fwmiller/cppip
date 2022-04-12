#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "buf.h"

void
bufq_test() {
    bufpool_t bp;
    bufq_t bq;
    time_t start, curr;

    bp = new bufpool(8, 64);
    printf("bufpool bufsize %d\r\n", bp->get_bufsize());
    bp->dump();

    bq = new bufq(8, 64);
    printf("bufq bufsize %d length %d\r\n", bq->get_bufsize(),
           bq->get_length());
    bq->dump();
    bq->dump_contents();
    printf("\r\n");

    srand(0);
    for (start = time(NULL);;) {
        if (rand() < RAND_MAX / 2) {
            // Get an buffer from bufpool and insert it in the queue
            buf_t buf = bp->pop();
            if (buf != NULL)
                bq->append(buf, 0);

        } else {
            // Remove a buffer from the queue and return it to bufpool
            int len;
            buf_t buf = bq->remove(&len);
            if (buf != NULL)
                bp->push(buf);
        }
        printf("bufpool bufsize %d\r\n", bp->get_bufsize());
        bp->dump();
        printf("bufq bufsize %d length %d\r\n", bq->get_bufsize(),
               bq->get_length());
        bq->dump();
        bq->dump_contents();
        printf("\r\n");

        curr = time(NULL);
        if (curr - start == 5)
            break;
    }
}

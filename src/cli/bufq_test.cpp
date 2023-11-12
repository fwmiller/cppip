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
    bq = new bufq(8, 64);
    srand(0);

    for (start = time(NULL);;) {
        if (rand() < RAND_MAX / 2) {
            // Get an buffer from bufpool and insert it in the queue
            bq->append(bp->pop(), 0);

        } else {
            // Remove a buffer from the queue and return it to bufpool
            int len = 0;
            bp->push(bq->remove(&len));
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

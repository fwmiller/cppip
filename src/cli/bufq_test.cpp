#include <stdio.h>
#include "buf.h"

void
bufq_test() {
    bufpool_t bp;
    bufq_t bq;

    bp = new bufpool(8, 64);
    printf("bufpool\r\n");
    bp->dump();

    bq = new bufq(8, 64);
    printf("bufq length %d bufsize %d\r\n", bq->get_length(),
           bq->get_bufsize());
    bq->dump();
    bq->dump_contents();
    printf("\r\n");

    for (;;) {
        buf_t buf = bp->pop();

        if (buf == NULL)
            break;

        bq->append(buf, 0);

        printf("bufpool\r\n");
        bp->dump();
        printf("bufq length %d bufsize %d\r\n", bq->get_length(),
               bq->get_bufsize());
        bq->dump();
        bq->dump_contents();
        printf("\r\n");
    }
}

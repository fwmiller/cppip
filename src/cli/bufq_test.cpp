#include "buf.h"

void
bufq_test() {
    bufpool_t bp;

    bp = new bufpool(8, 64);
    bp->dump();
}

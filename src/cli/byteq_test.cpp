#include "byteq.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void
byteq_test() {
    byteq q;
    char ch = 'a';
    char recv;
    time_t start, curr;

    for (start = time(NULL);;) {
        for (int i = 0; i < 10; i++) {
            q.append((buf_t) &ch, 1);
            q.dump_contents();
            printf("\r");

            if (ch == 'z')
                ch = 'a';
            else
                ch++;
        }
        for (int i = 0; i < 11; i++) {
            q.remove((buf_t) &recv, 1);
            q.dump_contents();
            printf("\r");
        }

        curr = time(NULL);
        if (curr - start == 5) {
            printf("\r\n");
            break;
        }
    }
}

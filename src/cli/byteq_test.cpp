#include "byteq.h"

void
byteq_test() {
    byteq q;
    char ch = 'a';
    char recv;

    for (;;) {
        for (int i = 0; i < 10; i++) {
            q.append((buf_t) &ch, 1);
            q.dump_contents();

            if (ch == 'z')
                ch = 'a';
            else
                ch++;
        }
        for (int i = 0; i < 11; i++) {
            q.remove((buf_t) &recv, 1);
            q.dump_contents();
        }
    }
}

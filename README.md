# cppip

cppip is an Internet protocol stack for embedded, real-time systems
written in C++.

cppip is specifically designed for statically managed networks that
use primarily UDP to pass application data.  Embedded, hard real-time
applications that make use of highly controlled Ethernet networks require
a protocol stack that is simple, high-performance, and verifiable.

cppip uses only the stack for dynamic memory during nominal operations.
Data structures are only allocated from the heap at initialization.

## Data Structures

The most basic data structure is the buffer which is simply a pointer to
a byte:

`typedef uint8_t *buf_t`

From this a buffer pool is created.  A buffer pool is a contiguous segment
of memory that has been divided into a contiguous set of buffers.  The
buffer pool manages allocations from this pool only.  No freeing of buffers
is supported.

There is also a buffer queue that manages a set of buffer pointers in a
First-In-First-Out queue.

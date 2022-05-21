# *cppip*

*cppip* is an Internet protocol stack for embedded, real-time systems written in C++.

*cppip* is specifically designed for statically managed networks that use primarily UDP to pass application data.  Embedded, hard real-time applications that make use of highly controlled Ethernet networks require a protocol stack that is high-performance, and verifiable.

*cppip* uses only the stack for dynamic memory after initialization.  Stack data structures are allocated from the heap only during initialization.

## Data Structures

The most basic data structure is the buffer pointer, `buf_t`, that is simply a pointer to a byte:

`typedef uint8_t *buf_t`

The intent of the `buf_t` is to provide a handle for a packet buffer including its headers and payload data.

Two aggregate data structures are defined based on the `buf_t` type.  The first is buffer pool that provides dynamic management of main memory allocated  pools of `buf_t` pointers.  The second is a buffer queue that provides a First-In-First-Out (FIFO) queue of `buf_t` pointers.

The following figure illustrates the relationships between these data structures:

<p align="center"><img src="doc/bufs.png"></p>

### Buffer Pools

A buffer pool is a contiguous segment of memory that has been divided into a contiguous list of fixed size buffers that are managed as a stack.

After the bufpool memory is allocated at initialization, it is divided into a sequence of fixed size buffer.  The base address of each of these buffers is then inserted into a stack data structure using a linked list of addresses that are stored in the first few bytes of each buffer.  The use of a stack enables constant time insertion and removal operations that are acceptable for hard real-time applications.

### Buffer Queues

A buffer queue is a First-In-First-Out (FIFO) queue of buffer pointers.  No buffer memory is allocated as part of this data structure, it manages buffer pointers only.  The queue head and tail are indexes into this buffer pointer array that advance in a circular manner, i.e. when a head or tail index reaches the end of the array, it returns to the first buffer pointer at the beginning of the array.  Buffer pointers are inserted at the tail of the queue and removed from the head of the queue.

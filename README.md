# cppip

cppip is an Internet protocol stack for embedded, real-time systems
written in C++.

cppip is specifically designed for statically managed networks that
use primarily UDP to pass application data.  Embedded, hard real-time
applications that make use of highly controlled Ethernet networks require
a protocol stack that is simple, high-performance, and verifiable.

cppip uses only the stack for dynamic memory during nominal operations.
Data structures are only allocated from the heap at initialization.

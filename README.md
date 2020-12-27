# cppip
cppip is an Internet protocol stack for embedded systems written in C++.

cppip is specifically designed for statically managed networks that
use primarily UDP to pass application data.  This means that the
various protocol addressing information is known prior to operations.

cppip uses only stack-based dynamic memory, it does not use the heap.

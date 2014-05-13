clean-amr
=========

amrnb and amrwb codec written by clean c99


differ from 3gpp source
=======================

I delete all memory alloc code, so it is now easy coding for concurrent programming,
 especially lots of parallel encoding and decoding tasks.

typedef.h change to using stdint.h, it is easy to support 32bit and 64bit platform
without change any code.

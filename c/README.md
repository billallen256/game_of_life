C implementation, intended to be very small to run on embedded platforms.  Along the way I decided to see how different compilers and architectures compare.

Benchmarks as of commit 7a163e53:

| Platform | CPU | OS | Compiler | Iterations | Time |
|----------|-----|----|----------|------------|------|
| Feather M0 | ATSAMD21 | None | gccarm 9.3.1 | 10,000 | 144s |
| PC Desktop | Core i5 3570K | FreeBSD 14.4 | clang 19 | 1,000,000 | 6.4s |
| PC Desktop | Core i7 8700 | Ubuntu 22.04 | gcc 14 | 1,000,000 | 6.2s |
| PC Desktop | Core i7 8700 | Ubuntu 22.04 | clang 20 | 1,000,000 | 3.6s |
| Mac Mini | Apple M1 | MacOS 26.5 | clang 21 | 1,000,000 | 2.51s |

The number of iterations was hard-coded, so in theory the compiler could have pre-computed the final result at compile time, but I saw no evidence of this; perhaps other languages will.  Also, you'll see unused functions in the code which were attempts to speed things up, but actually had the opposite effect.  Regardless, the entire world fits in 256 bytes (2 frames, 128 bytes/frame), which is well within the limit of L1 cache, if not the registers themselves.

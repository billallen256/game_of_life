C implementation using 64x64 bits instead of 32x32.

Benchmarks as of commit f08a12bf:

| Platform | CPU | OS | Compiler | Iterations | Time |
|----------|-----|----|----------|------------|------|
| Mac Mini | Apple M1 | MacOS 26.5 | clang 21 | 1,000,000 | 9.95s |

The board is four times the size of a 32x32, and is taking just slightly less than four times as long.  I also suspect that the compiler might be replacing the count_ones implementations with [a dedicated CPU instruction](https://kellegous.com/j/2023/07/24/counting-bits/) (as it should), though it doesn't get called until once at the end, so it's hard to know without digging into the assembly.

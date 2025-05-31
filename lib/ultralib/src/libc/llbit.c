#include "PR/ultratypes.h"

s64 __ll_bit_extract(u64* addr, unsigned int start_bit, unsigned int length) {
    unsigned int words;
    unsigned int lbits;
    unsigned int rbits;
    u64 mask;

    words = start_bit / 64;
    lbits = start_bit & (64 - 1);
    rbits = 64 - (lbits + length);

    addr += words;
    mask = ((u64)1 << length) - 1;
    mask = mask << rbits;
    return (s64)((*addr & mask) >> rbits);
}

u64 __ull_bit_extract(u64* addr, unsigned int start_bit, unsigned int length) {
    unsigned int words;
    unsigned int lbits;
    unsigned int rbits;
    u64 mask;

    words = start_bit / 64;
    lbits = start_bit & (64 - 1);
    rbits = 64 - (lbits + length);
    addr += words;
    mask = ((u64)1 << length) - 1;
    mask = mask << rbits;
    return (u64)((*addr & mask) >> rbits);
}

u64 __ll_bit_insert(u64* addr, unsigned int start_bit, unsigned int length, u64 val) {
    unsigned int words;
    unsigned int lbits;
    unsigned int rbits;
    unsigned long long llval;
    unsigned long long mask;

    words = start_bit / 64;
    lbits = start_bit & 0x3f;
    rbits = 64 - (lbits + length);
    addr += words;
    mask = ((u64)1 << length) - 1;
    mask <<= rbits;
    llval = (val << (64 - length)) >> lbits;
    *addr = (*addr & ~mask) | llval;
    llval = llval >> rbits;
    return llval;
}

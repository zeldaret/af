#ifndef LIBC_STDDEF_H
#define LIBC_STDDEF_H

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef _PTRDIFF_T
    #define _PTRDIFF_T
    #if (_MIPS_SZLONG == 32)
        typedef int ptrdiff_t;
    #else
        typedef long ptrdiff_t;
    #endif
#endif

#ifndef offsetof
#ifdef __GNUC__
#define offsetof(structure, member) __builtin_offsetof(structure, member)
#else
#define offsetof(structure, member) ((size_t)&(((structure*)0)->member))
#endif
#endif

#endif

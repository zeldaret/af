#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H


#if (!defined(__GNUC__) && !defined(__clang__)) || defined(M2CTX) || defined(__sgi)
    #ifndef __attribute__
        #define __attribute__(x)
    #endif
#endif


#ifndef FALLTHROUGH
    #ifdef PERMUTER
        #define FALLTHROUGH
    #elif __STDC_VERSION__ >= 202000L
        #define FALLTHROUGH [[fallthrough]]
    #else
        #define FALLTHROUGH __attribute__((fallthrough))
    #endif
#endif

#ifndef NORETURN
    #ifdef PERMUTER
        #define NORETURN
    #elif __STDC_VERSION__ >= 202000L
        #define NORETURN [[noreturn]]
    #elif __STDC_VERSION__ >= 201112L
        #define NORETURN _Noreturn
    #else
        #define NORETURN __attribute__((noreturn))
    #endif
#endif

#ifndef UNUSED
    #ifdef PERMUTER
        #define UNUSED
    #elif __STDC_VERSION__ >= 202000L
        #define UNUSED [[maybe_unused]]
    #else
        #define UNUSED __attribute__((unused))
    #endif
#endif


#endif

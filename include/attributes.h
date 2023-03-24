#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H


#if (!defined(__GNUC__) && !defined(__clang__)) || defined(M2CTX) || defined(__sgi)
    #ifndef __attribute__
        #define __attribute__(x)
    #endif
#endif


#ifndef CONST
    #if __STDC_VERSION__ >= 202000L
        #define CONST [[gnu::const]]
    #else
        #define CONST __attribute__((const))
    #endif
#endif

#ifndef DEPRECATED
    #if __STDC_VERSION__ >= 202000L
        #define DEPRECATED(reason) [[deprecated (reason)]]
    #else
        #define DEPRECATED(reason) __attribute__((deprecated (reason)))
    #endif
#endif

#ifndef FALLTHROUGH
    #if __STDC_VERSION__ >= 202000L
        #define FALLTHROUGH [[fallthrough]]
    #else
        #define FALLTHROUGH __attribute__((fallthrough))
    #endif
#endif

#ifndef NODISCARD
    #if __STDC_VERSION__ >= 202000L
        #define NODISCARD [[nodiscard]]
    #else
        #define NODISCARD __attribute__((warn_unused_result))
    #endif
#endif

#ifndef NORETURN
    #if __STDC_VERSION__ >= 202000L
        #define NORETURN [[noreturn]]
    #elif __STDC_VERSION__ >= 201112L
        #define NORETURN _Noreturn
    #else
        #define NORETURN __attribute__((noreturn))
    #endif
#endif

#ifndef PURE
    #if __STDC_VERSION__ >= 202000L
        #define PURE [[gnu::pure]]
    #else
        #define PURE __attribute__((pure))
    #endif
#endif

#ifndef RETURNS_NON_NULL
    #if __STDC_VERSION__ >= 202000L
        #define RETURNS_NON_NULL [[gnu::returns_nonnull]]
    #else
        #define RETURNS_NON_NULL __attribute__((returns_nonnull))
    #endif
#endif

#ifndef UNUSED
    #if __STDC_VERSION__ >= 202000L
        #define UNUSED [[maybe_unused]]
    #else
        #define UNUSED __attribute__((unused))
    #endif
#endif


#endif

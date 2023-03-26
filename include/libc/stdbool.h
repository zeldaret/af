#ifndef LIBC_STDBOOL_H
#define LIBC_STDBOOL_H

#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1
#endif

#ifndef __cplusplus

#if (__STDC_VERSION__ >= 199901L) && !defined(PERMUTER)
#define bool  _Bool
#define false 0
#define true  1
#elif CC_CHECK
// A way to enforce bools to not be treated the same as s32 by the host compiler
// This has to be an ifdef because an enum-return-type doesn't match on `return (thing1) && (thing2);` patterns
typedef enum bool {
    false,
    true
} bool;
#else
typedef int bool;

#define false   0
#define true    1
#endif

#endif /* __cplusplus */

#endif /* STDBOOL */

#ifndef LIBC_STDBOOL_H
#define LIBC_STDBOOL_H

#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1
#endif

#ifndef __cplusplus

#if (__STDC_VERSION__ >= 201112L) && !defined(PERMUTER)
#define bool _Bool
#define true 1
#define false 0
#else
typedef enum bool {
    false,
    true
} bool;
#endif

#endif /* __cplusplus */

#endif /* STDBOOL */

#ifndef UNK_H
#define UNK_H

#include "ultra64.h"

#define UNK_TYPE s32
#define UNK_TYPE1 s8
#define UNK_TYPE2 s16
#define UNK_TYPE4 s32
#define UNK_TYPE8 s64
#define UNK_PTR void*
#define UNK_RET UNK_TYPE
#define UNK_ARGS 
#define UNK_FUN_ARG void(*)(void)
//#define UNK_FUN_PTR(name) void(*name)(void)
typedef UNK_RET (*UNK_FUN_PTR)(UNK_ARGS);
#define UNK_SIZE 1

#endif

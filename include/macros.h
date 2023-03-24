#ifndef MACROS_H
#define MACROS_H

#if defined(_MSC_VER)
#  define UNREACHABLE __assume(0)
#elif defined(__GNUC__) || defined(__clang__)
#  define UNREACHABLE __builtin_unreachable()
#else
#  define UNREACHABLE
#endif

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240


#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))


#define saved_reg_s0 0
#define saved_reg_s1 0
#define saved_reg_s2 0
#define saved_reg_s3 0
#define saved_reg_s4 0
#define saved_reg_s5 0
#define saved_reg_s6 0
#define saved_reg_s7 0
#define bitwise
#define saved_reg_f20 0.0f
#define saved_reg_f22 0.0f


#endif

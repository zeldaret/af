#ifndef MACROS_H
#define MACROS_H

#if defined(__GNUC__) || defined(__clang__)
#define UNREACHABLE __builtin_unreachable()
#else
#define UNREACHABLE
#endif

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define ABS(x) (((x) >= 0) ? (x): -(x))

#endif

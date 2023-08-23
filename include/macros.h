#ifndef MACROS_H
#define MACROS_H

#if defined(__GNUC__) || defined(__clang__)
#define UNREACHABLE __builtin_unreachable()
#else
#define UNREACHABLE
#endif

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define PROJECTED_TO_SCREEN_X(projectedPos, invW) ((projectedPos).x * (invW) * (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 2))
#define PROJECTED_TO_SCREEN_Y(projectedPos, invW) ((projectedPos).y * (invW) * (-SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 2))

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define ABS(x) (((x) >= 0) ? (x): -(x))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))

#define DECR(x) ((x) == 0 ? 0 : --(x))

#endif

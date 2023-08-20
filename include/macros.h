#ifndef MACROS_H
#define MACROS_H

#include "ultra64.h"
#include "code_variables.h"

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

#define SEGMENTED_TO_K0(addr) (void*)((gSegments[SEGMENT_NUMBER(addr)] + K0BASE) + SEGMENT_OFFSET(addr))

#define ABS(x) (((x) >= 0) ? (x): -(x))
#define	ABS_F(x) (((x) >= 0.0f) ? (x) : -(x))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define CLAMP_MAX(x, max) ((x) > (max) ? (max) : (x))
#define CLAMP_MIN(x, min) ((x) < (min) ? (min) : (x))

#define DECR(x) ((x) == 0 ? 0 : --(x))

#define CHECK_FLAG_ALL(flags, mask) (((flags) & (mask)) == (mask))

#define DECR(x) ((x) == 0 ? 0 : --(x))

#endif

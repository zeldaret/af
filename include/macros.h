#ifndef MACROS_H
#define MACROS_H

#if defined(__GNUC__) || defined(__clang__)
#define UNREACHABLE __builtin_unreachable()
#else
#define UNREACHABLE
#endif

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Segment Wrapper
// Uncached RDRAM
#define KSEG1 0xA0000000 // 0xA0000000 - 0xBFFFFFFF  Physical memory, uncached, unmapped
#define RDRAM_UNCACHED KSEG1

// Cached RDRAM
#define KSEG0 0x80000000 // 0x80000000 - 0x9FFFFFFF  Physical memory, cached, unmapped
#define RDRAM_CACHED KSEG0

#define PHYSICAL_TO_VIRTUAL(addr) ((uintptr_t)(addr) + RDRAM_CACHED)
#define VIRTUAL_TO_PHYSICAL(addr) (uintptr_t)((u8*)(addr) - RDRAM_CACHED)
#define SEGMENTED_TO_VIRTUAL(addr) (void*)(PHYSICAL_TO_VIRTUAL(gSegments[SEGMENT_NUMBER(addr)]) + SEGMENT_OFFSET(addr))

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#endif

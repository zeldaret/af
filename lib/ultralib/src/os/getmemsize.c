#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PR/R4300.h"

#define STEP 0x100000
#define SIZE_4MB 0x400000
#define SIZE_8MB 0x800000

#if BUILD_VERSION >= VERSION_J

u32 osGetMemSize(void) {
    vu32* ptr;
    u32 size = SIZE_4MB;
    u32 data0;
    u32 data1;

    while (size < SIZE_8MB) {
        ptr = (vu32*)(K1BASE + size);

        data0 = *ptr;
        data1 = ptr[STEP / 4 - 1];

        *ptr ^= ~0;
        ptr[STEP / 4 - 1] ^= ~0;

        if ((*ptr != (data0 ^ ~0)) || (ptr[STEP / 4 - 1] != (data1 ^ ~0))) {
            return size;
        }

        *ptr = data0;
        ptr[STEP / 4 - 1] = data1;

        size += STEP;
    }

    return size;
}

#else

u32 osGetMemSize(void) {
    u32* memory;
    u32 memsize = SIZE_4MB - STEP;
    do {
        memsize += STEP;
        memory = (u32*)(memsize + K1BASE);
        memory[0] = 0x12345678;
        memory[STEP / 4 - 1]  = 0x87654321;
    } while (memory[0] == 0x12345678 && memory[STEP / 4 - 1] == 0x87654321);
    return memsize;
}

#endif

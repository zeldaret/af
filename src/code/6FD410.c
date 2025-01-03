#include "6FD410.h"

#include "libc/stdbool.h"

s32 B_80146080_jp;
UNK_PTR B_80146084_jp;

void func_800D9770_jp(void) {
    B_80146080_jp = 0;
    B_80146084_jp = NULL;
}

void func_800D9788_jp(void) {
    B_80146080_jp = 0;
    B_80146084_jp = NULL;
}

UNK_PTR func_800D97A0_jp(u32 arg0) {
    if (arg0 < 0x25800) {
        if (B_80146080_jp == 0) {
            B_80146080_jp = 1;
        } else if (B_80146080_jp == 3) {
            B_80146080_jp = 4;
            return B_80146084_jp;
        }
    }
    return NULL;
}

UNK_PTR func_800D97F8_jp(u32 arg0) {
    UNK_PTR ret;
    u32 start = osGetCount();

    while (true) {
        if ((osGetCount() - start) > ((s32)(OS_NSEC_TO_CYCLES(1333333334)))) {
            return 0;
        }

        ret = func_800D97A0_jp(arg0);
        if (ret != NULL) {
            return ret;
        }
    }
}

void func_800D986C_jp(s32 arg0) {
    if (arg0) {
        B_80146084_jp = NULL;
        B_80146080_jp = 0;
    }
}

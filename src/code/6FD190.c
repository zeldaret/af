#include "6FD190.h"

#include "alignment.h"
#include "libc64/malloc.h"
#include "6FD410.h"
#include "unk.h"

void* B_80146060_jp[3];
void* B_8014606C_jp;
uintptr_t B_80146070_jp;

uintptr_t func_800D94F0_jp(void) {
    B_80146070_jp = 0x80400000;
    B_80146070_jp &= ~0x3F;
    return B_80146070_jp;
}

void func_800D9514_jp(void) {
    B_80146070_jp = 0;
}

void func_800D9524_jp(void) {
    B_80146060_jp[0] = NULL;
    B_80146060_jp[1] = NULL;
    B_80146060_jp[2] = NULL;
    B_8014606C_jp = NULL;
    func_800D9770_jp();
}

extern UNK_TYPE D_80000400; // TODO: linker segment?

void func_800D955C_jp(s32 arg0) {
    switch (arg0) {
        case 0:
            B_80146060_jp[0] = &D_80000400;
            break;

        case 1:
            B_80146060_jp[1] = (void*)ALIGN64((uintptr_t)malloc_r(0x2583F));
            break;

        case 2:
            B_8014606C_jp = (void*)ALIGN64((uintptr_t)malloc(0x2583F));
            break;

        case 3:
            B_80146060_jp[2] = (void*)ALIGN64((uintptr_t)malloc(0x2583F));
            break;

        default:
            break;
    }
}

void func_800D9618_jp(s32 arg0) {
    switch (arg0) {
        case 0:
            *B_80146060_jp = NULL;
            break;

        case 1:
            free(B_80146060_jp[1]);
            B_80146060_jp[1] = NULL;
            break;

        case 2:
            free(B_8014606C_jp);
            B_8014606C_jp = NULL;
            break;

        case 3:
            free(B_80146060_jp[2]);
            B_80146060_jp[2] = NULL;
            break;

        default:
            break;
    }
}

void func_800D96A8_jp(void) {
    func_800D9788_jp();
    func_800D9618_jp(0);
    func_800D9618_jp(1);
    func_800D9618_jp(2);
    func_800D9618_jp(3);
}

void* func_800D96E8_jp(s32 arg0) {
    return B_80146060_jp[arg0];
}

s32 func_800D9700_jp(void) {
    if (B_80146060_jp[2] != NULL) {
        return 3;
    }

    if (B_80146060_jp[1] != NULL) {
        return 2;
    }

    if (B_80146060_jp[0] != NULL) {
        return 1;
    }

    return 0;
}

void* func_800D9750_jp(void) {
    return B_8014606C_jp;
}

uintptr_t func_800D9760_jp(void) {
    return B_80146070_jp;
}

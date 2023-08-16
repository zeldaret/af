#include "global.h"
#include "libc64/osmalloc.h"
#include "libc64/malloc.h"

typedef void (*BlockFunc)(void*);
typedef void (*BlockFunc1)(void*, u32);
typedef void (*BlockFunc8)(void*, u32, u32, u32, u32, u32, u32, u32, u32);

typedef struct InitFunc {
    /* 0x0 */ uintptr_t nextOffset;
    /* 0x4 */ void (*func)(void);
} InitFunc; // size = 0x8

extern void* D_8003C560_jp;

void* D_8003C560_jp = NULL;

char D_8003C564_jp[] = "";

UNK_TYPE1 D_8003C568_jp[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x00, 0x00,
    0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
};

void* func_8002BC60_jp(size_t size) {
    if (size == 0) {
        size = 1;
    }
    return __osMalloc(&malloc_arena, size);
}

void func_8002BC90_jp(void* ptr) {
    if (ptr != 0) {
        __osFree(&malloc_arena, ptr);
    }
}

void func_8002BCBC_jp(void* blk, size_t nBlk, size_t blkSize, BlockFunc blockFunc) {
    uintptr_t pos = (uintptr_t)blk;

    for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
        blockFunc((void*)pos);
    }
}

void func_8002BD2C_jp(void* blk, size_t nBlk, size_t blkSize, BlockFunc1 blockFunc) {
    uintptr_t pos = (uintptr_t)blk;

    for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
        blockFunc((void*)pos, 2);
    }
}

void* func_8002BD9C_jp(void* blk, size_t nBlk, size_t blkSize, BlockFunc8 blockFunc) {
    if (blk == NULL) {
        blk = func_8002BC60_jp(nBlk * blkSize);
    }

    if ((blk != NULL) && (blockFunc != NULL)) {
        uintptr_t pos = (uintptr_t)blk;

        for (; pos < (uintptr_t)blk + (nBlk * blkSize); pos += (blkSize & ~0)) {
            blockFunc((void*)pos, 0, 0, 0, 0, 0, 0, 0, 0);
        }
    }

    return blk;
}

void func_8002BE6C_jp(void* blk, size_t nBlk, size_t blkSize, BlockFunc1 blockFunc, s32 shouldFree) {
    uintptr_t pos;
    uintptr_t start;
    size_t maskedBlkSize;

    if (blk == NULL) {
        return;
    }

    if (blockFunc != NULL) {
        start = (uintptr_t)blk;
        maskedBlkSize = (blkSize & ~0);
        pos = (uintptr_t)start + (nBlk * blkSize);

        while (pos > start) {
            pos -= maskedBlkSize;
            blockFunc((void*)pos, 2);
        }
    }

    if (shouldFree) {
        func_8002BC90_jp(blk);
    }
}

void func_8002BF08_jp(void) {
    InitFunc* initFunc = (InitFunc*)&D_8003C560_jp;
    u32 nextOffset = initFunc->nextOffset;
    InitFunc* prev = NULL;

    while (nextOffset != 0) {
        initFunc = (InitFunc*)((uintptr_t)initFunc + nextOffset);

        if (initFunc->func != NULL) {
            (*initFunc->func)();
        }

        nextOffset = initFunc->nextOffset;
        initFunc->nextOffset = (uintptr_t)prev;
        prev = initFunc;
    }

    D_8003C560_jp = prev;
}

void func_8002BF78_jp(void* heap, size_t size) {
    MallocInit(heap, size);
    func_8002BF08_jp();
}

#ifndef _FINALROM

#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "osint.h"

#include "macros.h"

typedef struct {
    /* 0x0 */ unsigned int inst1;
    /* 0x4 */ unsigned int inst2;
    /* 0x8 */ unsigned int inst3;
    /* 0xC */ unsigned int inst4;
} __osExceptionVector;

extern __osExceptionVector __isExpJP;

void MonitorInitBreak(void);

typedef struct {
    /* 0x00 */ u32 magic; // IS64
    /* 0x04 */ u32 get;
    /* 0x08 */ u8 unk_08[0x14 - 0x08];
    /* 0x14 */ u32 put;
    /* 0x18 */ u8 unk_18[0x20 - 0x18];
    /* 0x20 */ u8 data[0x10000 - 0x20];
} ISVDbg;

#define IS64_MAGIC 'IS64'

__osExceptionVector ramOldVector ALIGNED(8);
u32 gISVFlag;
u16 gISVChk;
ISVDbg* gISVDbgPrnAdrs;
u32 leoComuBuffAdd;

static OSPiHandle* is_Handle;

void isPrintfInit(void) {
    is_Handle = osCartRomInit();

    osEPiWriteIo(is_Handle, &gISVDbgPrnAdrs->put, 0);
    osEPiWriteIo(is_Handle, &gISVDbgPrnAdrs->get, 0);
    osEPiWriteIo(is_Handle, &gISVDbgPrnAdrs->magic, IS64_MAGIC);
}

static void* is_proutSyncPrintf(void* arg, const u8* str, u32 count) {
    u32 data;
    s32 p;
    s32 start;
    s32 end;
    u32* magic = &gISVDbgPrnAdrs->magic;

    if (gISVDbgPrnAdrs == NULL) {
        return 0;
    }

    osEPiReadIo(is_Handle, (u32)magic, &data);
    if (data != IS64_MAGIC) {
        return 1;
    }
    osEPiReadIo(is_Handle, (u32)&gISVDbgPrnAdrs->get, &data);
    p = data;
    osEPiReadIo(is_Handle, (u32)&gISVDbgPrnAdrs->put, &data);

    start = data;
    end = start + count;

    if (end >= 0xffe0) {
        end -= 0xffe0;
        if (p < end || start < p) {
            return 1;
        }
    } else {
        if (start < p && p < end) {
            return 1;
        }
    }
    while (count) {
        if (*str != '\0') {
            s32 shift = start & 3;
            u32 addr = (u32)&gISVDbgPrnAdrs->data[start & 0xFFFFFFC];

            shift = (3 - shift) * 8;

            osEPiReadIo(is_Handle, addr, &data);
            osEPiWriteIo(is_Handle, addr, (data & ~(0xff << shift)) | (*str << shift));

            start++;
            if (start >= 0xffe0) {
                start -= 0xffe0;
            }
        }
        count--;
        str++;
    }
    osEPiWriteIo(is_Handle, (u32)&gISVDbgPrnAdrs->put, start);

    return 1;
}

int __checkHardware_isv(void) {
    u32 i = 0;
    u32 data;
    u32 save[4];
    OSPiHandle* hnd = osCartRomInit();

    gISVDbgPrnAdrs = NULL;
    leoComuBuffAdd = 0;
    gISVFlag = IS64_MAGIC;
    gISVChk = 0;

    for (i = 0; i < 4; i++) {
        osEPiReadIo(hnd, 0xB0000100 + i * 4, &save[i]);
    }

#ifndef __GNU__ // BUG: data is used uninitialized for GCC
    data = 0;
#endif
    osEPiWriteIo(hnd, 0xB000010C, data);
    data = IS64_MAGIC;
    osEPiWriteIo(hnd, 0xB0000100, IS64_MAGIC);

    for (i = 0; i < 0x20000; i++) {
        osEPiReadIo(hnd, 0xB000010C, &data);
        if (data == IS64_MAGIC) {
            data = 0;
            osEPiWriteIo(hnd, 0xB0000100, data);
            gISVChk |= 1;
            osEPiReadIo(hnd, 0xB0000104, (void*)&gISVDbgPrnAdrs);
            osEPiReadIo(hnd, 0xB0000108, &leoComuBuffAdd);
            break;
        }
    }

    for (i = 0; i < 4; i++) {
        osEPiWriteIo(hnd, 0xB0000100 + i * 4, save[i]);
    }

    osEPiReadIo(hnd, 0xBFF00000, &data);

    gISVChk |= ((data == IS64_MAGIC) ? 2 : 0);

    return (gISVChk != 0) ? TRUE : FALSE;
}

void __osInitialize_isv(void) {
    void (*fn)(void);
    OSPiHandle* hnd;
    s32 pad;
    s32 pad2;

    if (gISVFlag == IS64_MAGIC || __checkHardware_isv()) {
        if (gISVDbgPrnAdrs != NULL) {
            __printfunc = is_proutSyncPrintf;
            isPrintfInit();
        }
        if (gISVChk & 2) {
            hnd = osCartRomInit();

            ramOldVector = *(__osExceptionVector*)E_VEC;
            *(__osExceptionVector*)E_VEC = __isExpJP;

            osWritebackDCache(&ramOldVector, 0x10);
            osInvalICache(&ramOldVector, 0x10);
            osWritebackDCache(0x80000000, 0x190);
            osInvalICache(0x80000000, 0x190);
            osEPiReadIo(hnd, 0xBFF00010, (u32*)&fn);
            fn();
        }
        if (gISVChk & 2) {
            MonitorInitBreak();
        }
    }
}

#endif

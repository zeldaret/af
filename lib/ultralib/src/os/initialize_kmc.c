#ifndef _FINALROM

#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PRinternal/osint.h"

typedef struct {
    /* 0x0 */ unsigned int inst1;
    /* 0x4 */ unsigned int inst2;
    /* 0x8 */ unsigned int inst3;
    /* 0xC */ unsigned int inst4;
} __osExceptionVector;

extern __osExceptionVector __ptExceptionPreamble[];

static volatile unsigned int* stat = (unsigned*)0xbff08004;
static volatile unsigned int* wport = (unsigned*)0xbff08000;
static volatile unsigned int* piok = (unsigned*)PHYS_TO_K1(PI_STATUS_REG);

static void rmonPutchar(char c) {
    u32 data;

    while (TRUE) {
        osPiReadIo(stat, &data);
        if (data & 4) {
            osPiWriteIo(wport, c);
            break;
        }
    }
}

static void* kmc_proutSyncPrintf(void* str, const char* buf, int n) {
    int i;
    char c;
    char* p;
    char* q;
    char xbuf[128];
    static int column = 0;

    p = &xbuf;

    for (i = 0; i < n; i++) {
        c = *buf++;

        switch (c) {
            case '\n':
                *p++ = '\n';
                column = 0;
                break;
            case '\t':
                do {
                    *p++ = ' ';
                } while (++column % 8);
                break;
            default:
                column++;
                *p++ = c;
                break;
        }

        if (c == '\n' || (p - xbuf) > 100) {
            rmonPutchar((p - xbuf) - 1);

            q = xbuf;
            while (q != p) {
                rmonPutchar(*q++);
            }
            p = xbuf;
        }
    }
    if (p != xbuf) {
        rmonPutchar((p - xbuf) - 1);

        q = xbuf;
        while (q != p) {
            rmonPutchar(*q++);
        }
    }
    return (void*)1;
}

extern u32 __kmc_pt_mode;

void __osInitialize_kmc(void) {
    if (!__kmc_pt_mode) {
        int (*fnc)();
        unsigned int* src;
        unsigned int* dst;
        unsigned int monadr;
        volatile unsigned int* mon;
        volatile unsigned int* stat;

        stat = (unsigned*)0xbff08004;
        mon = (unsigned*)0xBFF00000;
        if (*mon != 0x4B4D4300) {
            return;
        }

        src = (unsigned*)__ptExceptionPreamble;
        dst = (unsigned*)E_VEC;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        src += 2;
        dst += 2;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;

        osWritebackDCache(E_VEC, 0x24);
        osInvalICache(E_VEC, 0x24);

        __kmc_pt_mode = TRUE;

        if ((*stat & 0x10) == 0) {
            monadr = *(mon + 1);
            if (monadr != 0xBFF00000) {
                unsigned int* src;
                unsigned int* dst = monadr | 0x20000000;
                unsigned int ct = 0x2000 / 4;

                src = 0xBFF00000;

                while (ct != 0) {
                    *dst++ = *src++;
                    ct--;
                }
            }
            fnc = monadr + 8;
            fnc(0x4B4D4300, 0);
        }
        __printfunc = kmc_proutSyncPrintf;
    }
}

int __checkHardware_kmc(void) {
    volatile unsigned int* mon = (unsigned*)0xBFF00000;

    if (*mon == 0x4B4D4300) {
        mon = (unsigned*)0xBFF00010;

        if (*mon == 0xB0FFB000) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }
}

#endif

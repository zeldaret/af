#include "PR/os_internal.h"
#include "PR/os_version.h"
#include "PR/rcp.h"
#include "memory.h"

#include "PRinternal/macros.h"

#if BUILD_VERSION >= VERSION_J || !defined(_FINALROM)

static volatile unsigned int* ptwtmode = (unsigned*)0xbff08014;
static volatile unsigned int* ptstat = (unsigned*)0xbff08004;
static volatile unsigned int* ptport = (unsigned*)0xbff08000;
static volatile unsigned int* n64piok = (unsigned*)PHYS_TO_K1(PI_STATUS_REG);

static OSMesgQueue waitPtQueue ALIGNED(0x8);
static OSMesg waitPtQueueBuf;
static u32 isWaitPtQueueCreated = FALSE;

void __osPiRelAccess(void);
void __osPiGetAccess(void);

static void createWaitPtQueue(void) {
    osCreateMesgQueue(&waitPtQueue, &waitPtQueueBuf, 1);
    isWaitPtQueueCreated = TRUE;
}

static u32 getPT_wait(void) {
    OSTimer waitTimer;
    u32 status UNUSED;

    for (;;) {
        while (*n64piok & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
            ;
        }

        if (*ptstat & 2) {
            return *ptport;
        }
        __osPiRelAccess();

        osRecvMesg(&waitPtQueue, NULL, OS_MESG_NOBLOCK);
        osSetTimer(&waitTimer, OS_USEC_TO_CYCLES(1000), 0, &waitPtQueue, NULL);
        osRecvMesg(&waitPtQueue, NULL, OS_MESG_BLOCK);

        __osPiGetAccess();
    }
}

static void putPT(u32 c) {
    while (*n64piok & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
        ;
    }
    while (!(*ptstat & 4)) {
        ;
    }
    *ptport = c;
}

static u32 getPT(void) {
    while (*n64piok & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
        ;
    }
    while (!(*ptstat & 2)) {
        ;
    }
    return *ptport;
}

void osReadHost_pt(void* dramAddr, u32 nbytes) {
    u8* tPtr;
    u32 buf[256];
    u32* bp;
    u32 data;
    u32 ct;
    u32 ct1;
    u32 ct1_bak;
    u32 shift;
    u32 cmd;
    u32 size;

    if (nbytes == 0) {
        return;
    }

    if (!isWaitPtQueueCreated) {
        createWaitPtQueue();
    }

    __osPiGetAccess();

    putPT(0x82U);

    cmd = getPT_wait();

    size = getPT();

    if (cmd != 2) {
        nbytes = -1U;
    }

    putPT(nbytes);

    if (size != nbytes) {
        goto osReadHost_ret;
    }

    tPtr = dramAddr;
    ct = nbytes / 4;

    while (ct != 0) {
        if (ct > 0x100) {
            ct1_bak = ct1 = 0x100;
            ct -= 0x100;
        } else {
            ct1_bak = ct1 = ct;
            ct = 0;
        }
        bp = (u32*)&buf;

        while (ct1 != 0) {
            *(bp++) = getPT();
            ct1--;
        }

        memcpy(tPtr, &buf, ct1_bak * 4);
        tPtr += ct1_bak * 4;
    }

    nbytes &= 3;

    if (nbytes != 0) {
        data = getPT();
        shift = 0x18;

        do {
            *(tPtr++) = (data >> shift);
            nbytes--;
            shift -= 8;
        } while (nbytes != 0);
    }

osReadHost_ret:
    __osPiRelAccess();
    return;
}

void osWriteHost_pt(void* dramAddr, u32 nbytes) {
    u8* tPtr;
    u32 buf[256];
    u32* bp;
    u32 ct;
    u32 ct1;
    u32 ct1_bak;
    u32 cmd;
    u32 size;

    if (nbytes == 0) {
        return;
    }

    if (!isWaitPtQueueCreated) {
        createWaitPtQueue();
    }

    __osPiGetAccess();
    putPT(0x82);

    cmd = getPT_wait();

    size = getPT();

    if (cmd != 3) {
        nbytes = -1;
    }

    putPT(nbytes);

    if (size != nbytes) {
        goto osWriteHost_ret;
    }

    tPtr = dramAddr;
    ct = (nbytes + 3) >> 2;

    while (ct != 0) {
        if (ct > 0x100) {
            ct1_bak = ct1 = 0x100;
            ct -= 0x100;
        } else {
            ct1_bak = ct1 = ct;
            ct = 0;
        }

        memcpy(bp = buf, tPtr, ct1_bak * 4);

        while (ct1 != 0) {
            putPT(*(bp++));
            ct1--;
        }

        tPtr += ct1_bak * 4;
    }

osWriteHost_ret:
    __osPiRelAccess();
    return;
}

#endif

#include "ovlmgr.h"

#include "fault.h"
#include "loadfragment.h"
#include "malloc.h"
#include "m_malloc.h"
#include "z_std_dma.h"

void* ovlmgr_Malloc(size_t size) {
    void* ptr;

    if (zelda_MallocIsInitalized()) {
        ptr = zelda_malloc_r(size);
    } else {
        ptr = malloc_r(size);
    }

    return ptr;
}

void ovlmgr_Free(void* ptr) {
    if (zelda_MallocIsInitalized()) {
        zelda_free(ptr);
    } else {
        free(ptr);
    }
}

//#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/ovlmgr/ovlmgr_LoadImpl.s")
void ovlmgr_LoadImpl(void* vromStart, UNUSED UNK_TYPE arg1, void* vramStart, void* vramEnd, void* allocatedRamAddr,
                     struct OverlayRelocationSection* ovl, size_t size) {
    void* vromEnd;
    void* ovlStart;
    void* ovlEnd;
    size_t ovlSize;
    OverlayRelocationSection* ovlRelocs;
    char ovlSizeStr[80];

    func_80026C4C_jp(vromStart, &vromEnd, &ovlStart, &ovlEnd);

    ovlSize = (uintptr_t)ovlEnd - (uintptr_t)ovlStart;

    if ((ovl == NULL) || (size < ovlSize)) {
        ovlRelocs = ovlmgr_Malloc(ovlSize);
    } else {
        ovlRelocs = ovl;
    }

    if (ovlRelocs == NULL) {
        sprintf(ovlSizeStr, "%ld", ovlSize);
        Fault_AddHungupAndCrashImpl("ovlmgr: Out of Memory", ovlSizeStr);
    }

    Overlay_Load(vromStart, vromEnd, ovlStart, ovlEnd, vramStart, vramEnd, allocatedRamAddr, ovlRelocs);
    if (size < ovlSize) {
        ovlmgr_Free(ovlRelocs);
    }
}

void ovlmgr_Load(void* vromStart, UNK_TYPE arg1, void* vramStart, void* vramEnd, void* allocatedRamAddr) {
    ovlmgr_LoadImpl(vromStart, arg1, vramStart, vramEnd, allocatedRamAddr, NULL, 0);
}

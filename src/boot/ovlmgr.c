#include "ovlmgr.h"

#include "attributes.h"
#include "fault.h"
#include "loadfragment.h"
#include "libc64/malloc.h"
#include "m_malloc.h"
#include "libc64/sprintf.h"
#include "m_std_dma.h"

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

void ovlmgr_LoadImpl(RomOffset vromStart, UNUSED RomOffset vromEndUnused, void* vramStart, void* vramEnd,
                     void* allocatedRamAddr, struct OverlayRelocationSection* ovl, size_t size) {
    RomOffset vromEnd;
    RomOffset ovlStart;
    RomOffset ovlEnd;
    size_t ovlSize;
    OverlayRelocationSection* ovlRelocs;
    char ovlSizeStr[80];

    DmaMgr_GetOvlOffsets(vromStart, &vromEnd, &ovlStart, &ovlEnd);

    ovlSize = (uintptr_t)ovlEnd - (uintptr_t)ovlStart;

    if ((ovl == NULL) || (size < ovlSize)) {
        ovlRelocs = ovlmgr_Malloc(ovlSize);
    } else {
        ovlRelocs = ovl;
    }

    if (ovlRelocs == NULL) {
        sprintf(ovlSizeStr, "%ld", ovlSize);
        fault_AddHungupAndCrashImpl("ovlmgr: Out of Memory", ovlSizeStr);
    }

    Overlay_Load(vromStart, vromEnd, ovlStart, ovlEnd, vramStart, vramEnd, allocatedRamAddr, ovlRelocs);
    if (size < ovlSize) {
        ovlmgr_Free(ovlRelocs);
    }
}

void ovlmgr_Load(RomOffset vromStart, RomOffset vromEnd, void* vramStart, void* vramEnd, void* allocatedRamAddr) {
    ovlmgr_LoadImpl(vromStart, vromEnd, vramStart, vramEnd, allocatedRamAddr, NULL, 0);
}

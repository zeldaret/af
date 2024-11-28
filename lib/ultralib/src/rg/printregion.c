#include "os_version.h"
#if !defined(_FINALROM) || BUILD_VERSION < VERSION_J

#include "PRinternal/osint.h"
#include "PR/rmon.h"
#include "PR/region.h"

void __osPrintRegion(void* region) {
    register OSRegion* rp = region;
    int i;

    rmonPrintf("Region = 0x%x\n", rp);
    rmonPrintf("\tstartBufferAddress = 0x%x\n", RP(startBufferAddress));
    rmonPrintf("\tendAddress         = 0x%x\n", RP(endAddress));
    rmonPrintf("\tbufferSize         = %d\n", RP(bufferSize));
    rmonPrintf("\tbufferCount        = %d\n", RP(bufferCount));
    rmonPrintf("\tfreeList           = %d\n", RP(freeList));
    rmonPrintf("\talignSize          = %d\n", RP(alignSize));
    rmonPrintf("\tMemory Header Layout:\n");

    for (i = 0; i < RP(bufferCount); i++) {
        rmonPrintf("\tBuf[%d]:\tAddress: 0x%x  Value: 0x%x\n", i, RP(startBufferAddress) + i * RP(bufferSize),
                   *(u16*)(RP(startBufferAddress) + i * RP(bufferSize)));
    }
}

#endif

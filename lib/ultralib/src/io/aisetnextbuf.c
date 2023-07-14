#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "../os/osint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 osAiSetNextBuffer(void *bufPtr, u32 size) {
	static u8 hdwrBugFlag = FALSE;
	char *bptr;

	if (__osAiDeviceBusy()) {
		return -1;
	}

    bptr = bufPtr;

	if (hdwrBugFlag) {
		bptr -= 0x2000;
	}

	if ((((u32)bufPtr + size) & 0x1fff) == 0) {
		hdwrBugFlag = TRUE;
	} else {
		hdwrBugFlag = FALSE;
	}

	IO_WRITE(AI_DRAM_ADDR_REG, osVirtualToPhysical(bptr));
	IO_WRITE(AI_LEN_REG, size);
	return 0;
}

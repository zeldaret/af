#include "PR/os_internal.h"
#include "piint.h"

OSMesgQueue *osPiGetCmdQueue(void) {
    if (!__osPiDevMgr.active) {
        return NULL;
    }
    
    return __osPiDevMgr.cmdQueue;
}

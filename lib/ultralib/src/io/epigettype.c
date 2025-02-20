#include "PRinternal/piint.h"

s32 osEPiGetDeviceType(OSPiHandle* pihandle, OSPiInfo* info) {
    info->type = pihandle->type;
    info->address = pihandle->baseAddress;
    return 0;
}

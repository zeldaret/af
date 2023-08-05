#include "PR/os_internal.h"
#include "PR/R4300.h"

void* osPhysicalToVirtual(u32 addr) {
    return (void*)PHYS_TO_K0(addr);
}

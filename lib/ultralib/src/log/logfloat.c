#include "os_version.h"

#if !defined(_FINALROM) || BUILD_VERSION < VERSION_J

#include "ultralog.h"

u32 osLogFloat(f32 f) {
    return OS_LOG_FLOAT(f);
}

#endif

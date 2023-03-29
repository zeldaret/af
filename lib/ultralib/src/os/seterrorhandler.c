#include "PR/ultraerror.h"

extern OSErrorHandler __osErrorHandler;

OSErrorHandler osSetErrorHandler(OSErrorHandler handler) {
    OSErrorHandler oldHandler = __osErrorHandler;

    __osErrorHandler = handler;
    return oldHandler;
}

// This file was removed in 2.0J
#include "stdarg.h"
#include "PR/os_internal.h"
#include "PR/ultralog.h"
#include "PR/ultraerror.h"
#include "PRinternal/macros.h"

void __osLogWrite(OSLog* log, s16 code, s16 numArgs, va_list argPtr);
static void __osDefaultHandler(s16 code, s16 numArgs, ...);

static u32 errorLogData[19] ALIGNED(0x8);
static OSLog errorLog ALIGNED(0x8) = {
    OS_ERROR_MAGIC, // magic
    sizeof(errorLogData), // len
    errorLogData, // base
    0, //startCount
    0, //writeOffset
};

OSErrorHandler __osErrorHandler = __osDefaultHandler;

static void __osDefaultHandler(s16 code, s16 numArgs, ...) {
    va_list argPtr;
    va_start(argPtr, numArgs);

    __osLogWrite(&errorLog, code, numArgs, argPtr);
    osFlushLog(&errorLog);

    va_end(argPtr);
}

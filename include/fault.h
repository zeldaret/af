#ifndef FAULT_H
#define FAULT_H

#include "ultra64.h"
#include "unk.h"
#include "attributes.h"
#include "libc/stdarg.h"
#include "libc/stdint.h"
#include "libu64/pad.h"
#include "stack.h"

// These are the same as the 3-bit ansi color codes
#define FAULT_COLOR_BLACK      0
#define FAULT_COLOR_RED        1
#define FAULT_COLOR_GREEN      2
#define FAULT_COLOR_YELLOW     3
#define FAULT_COLOR_BLUE       4
#define FAULT_COLOR_MAGENTA    5
#define FAULT_COLOR_CYAN       6
#define FAULT_COLOR_WHITE      7
// Additional color codes
#define FAULT_COLOR_DARK_GRAY  8
#define FAULT_COLOR_LIGHT_GRAY 9

#define FAULT_COLOR_STRINGIFY(s) #s
#define FAULT_COLOR_EXPAND_AND_STRINGIFY(s) FAULT_COLOR_STRINGIFY(s)

#define FAULT_ESC '\x1A'
#define FAULT_COLOR(n) "\x1A" FAULT_COLOR_EXPAND_AND_STRINGIFY(FAULT_COLOR_ ## n)


typedef void (*FaultClientCallback)(void*, void*);

// TODO: taken from MM, needs to be verified
typedef struct FaultClient {
    /* 0x0 */ struct FaultClient* next;
    /* 0x4 */ FaultClientCallback callback;
    /* 0x8 */ void* arg0;
    /* 0xC */ void* arg1;
} FaultClient; // size = 0x10


typedef uintptr_t (*FaultAddrConvClientCallback)(uintptr_t, void*);

// TODO: taken from MM, needs to be verified
typedef struct FaultAddrConvClient {
    /* 0x0 */ struct FaultAddrConvClient* next;
    /* 0x4 */ FaultAddrConvClientCallback callback;
    /* 0x8 */ void* arg;
} FaultAddrConvClient; // size = 0xC

typedef struct FaultMgr {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ STACK(stack, 0x600); // probably an unused internal thread stack for `fault_ClientRunTask`/`clientThreadSp`
    /* 0x7B0 */ OSMesgQueue queue;
    /* 0x7C8 */ OSMesg msg[1];
    /* 0x7CC */ u8 exit;
    /* 0x7CD */ u8 msgId;
    /* 0x7CE */ u8 faultHandlerEnabled;
    /* 0x7CF */ u8 autoScroll;
    /* 0x7D0 */ OSThread* faultedThread;
    /* 0x7D4 */ void (*padCallback)(Input* inputs);
    /* 0x7D8 */ FaultClient* clients;
    /* 0x7DC */ FaultAddrConvClient* addrConvClients;
    /* 0x7E0 */ UNK_TYPE1 unk_7E0[0x4];
    /* 0x7E4 */ Input inputs[MAXCONTROLLERS];
    /* 0x844 */ void* fb;
    /* 0x848 */ void* clientThreadSp;
} FaultMgr; // size = 0x850


void fault_AddClient(FaultClient* client, FaultClientCallback callback, void* arg0, void* arg1);
void fault_RemoveClient(FaultClient* client);
void fault_AddressConverterAddClient(FaultAddrConvClient* client, FaultAddrConvClientCallback callback, void* arg);
void fault_AddressConverterRemoveClient(FaultAddrConvClient* client);
void fault_WaitForInput(void);
void fault_FillScreenBlack(void);
void fault_SetFrameBuffer(void* fb, u16 w, u16 h);
void fault_DrawStackTrace(OSThread* thread, s32 x, s32 y, s32 height);
void fault_Init(void);
NORETURN void fault_AddHungupAndCrashImpl(const char* exp1, const char* exp2);
NORETURN void fault_AddHungupAndCrash(const char* file, s32 line);
void FaultDrawer_SetOsSyncPrintfEnabled(u32 enabled);
void FaultDrawer_DrawRecImpl(s32 xStart, s32 yStart, s32 xEnd, s32 yEnd, u16 color);
void FaultDrawer_SetForeColor(u16 color);
void FaultDrawer_SetBackColor(u16 color);
void FaultDrawer_SetFontColor(u16 color);
void FaultDrawer_SetCharPad(s8 padW, s8 padH);
void FaultDrawer_SetCursor(s32 x, s32 y);
void FaultDrawer_FillScreen(void);
s32 FaultDrawer_VPrintf(const char* fmt, va_list args);
s32 FaultDrawer_Printf(const char* fmt, ...);
void FaultDrawer_DrawText(s32 x, s32 y, const char* fmt, ...);
void FaultDrawer_SetDrawerFB(void* fb, u16 w, u16 h);
void FaultDrawer_SetInputCallback(void (*callback)(void));
void FaultDrawer_WritebackFBDCache(void);
void FaultDrawer_Init(void);

extern FaultMgr fault_class;

#endif

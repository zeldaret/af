#ifndef PADMGR_H
#define PADMGR_H

#include "ultra64.h"
#include "libu64/pad.h"

typedef struct padmgr{
    /* 0x00 */ u8 _0;
    /* 0x04 */ void (*rumbleRetraceCallback)(void*);
    /* 0x08 */ void* rumbleRetraceArg;
    /* 0x0C */ void (*inputRetraceCallback)(void*);
    /* 0x10 */ void* inputRetraceArg;
    /* 0x14 */ u8 _14[0x2B0 - 0x14];
    /* 0x2B0 */ OSContPad pads[MAXCONTROLLERS];
    /* 0x2C8 */ u8 _2C8[0x480 - 0x2C8];
} Padmgr; // size = 0x480

#define PADMGR_SET_RETRACE_CALLACK(callback, arg) \
    do {                                                  \
        padmgr_class.inputRetraceCallback = (callback);           \
        padmgr_class.inputRetraceArg = (arg);             \
    } while (0)

#define PADMGR_UNSET_RETRACE_CALLACK(callback, param) \
do { \
  Padmgr* mgr = &padmgr_class; \
  if (mgr->inputRetraceCallback == (callback) && mgr->inputRetraceArg == (param)) { \
    mgr->inputRetraceCallback = NULL; \
    mgr->inputRetraceArg = NULL; \
  } \
} while (0)


// void padmgr_LockSerialMesgQ();
// void padmgr_UnlockSerialMesgQ();
// void padmgr_LockContData();
// void padmgr_UnlockContData();
// void func_800D6AD4_jp();
// void func_800D6AEC_jp();
// void func_800D6B0C_jp();
// void func_800D6B34_jp();
// void padmgr_PakConnectCheck();
// void padmgr_HandleDoneReadPadMsg();
// void padmgr_ConnectCheck();
// void padmgr_HandleRetraceMsg();
// void padmgr_HandlePreNMIMsg();
// void padmgr_RequestPadData_NonLock();
void padmgr_RequestPadData(Input inputs[4], s32 arg1);
void padmgr_ClearPadData(Input inputs[4]);
// void padmgr_MainProc();
// void padmgr_Init();
// void func_800D763C_jp();
// void func_800D765C_jp();
// void func_800D7678_jp();

extern Padmgr padmgr_class;

#endif

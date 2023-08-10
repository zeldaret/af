#ifndef PADMGR_H
#define PADMGR_H

#include "ultra64.h"
#include "libu64/pad.h"

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

#endif

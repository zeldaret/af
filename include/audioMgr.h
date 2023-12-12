#ifndef AUDIOMGR_H
#define AUDIOMGR_H

#include "ultra64.h"
#include "sched.h"
#include "unk.h"
#include "71A140.h"

struct Irqmgr;
struct SchedContext;

typedef struct Audiomgr {
    /* 0x000 */ struct Irqmgr* irqMgr;
    /* 0x004 */ struct SchedContext* sched;
    /* 0x008 */ OSScTask audioTask;
    /* 0x060 */ AudioTask* rspTask;
    /* 0x064 */ OSMesgQueue interruptQueue;
    /* 0x07C */ OSMesg interruptMsgBuf[8];
    /* 0x09C */ OSMesgQueue cmdQueue;
    /* 0x0B4 */ OSMesg cmdMsgBuf[1];
    /* 0x0B8 */ OSMesgQueue lockQueue;
    /* 0x0D0 */ OSMesg lockMsgBuf[1];
    /* 0x0D4 */ UNK_TYPE1 unk_D4[0x4];
    /* 0x0D8 */ OSThread thread;
    /* 0x288 */ UNK_TYPE1 unk_288[2];
    /* 0x28A */ u8 unk_28A;
    /* 0x28B */ u8 unk_28B;
} Audiomgr; //size = 0x290


// void func_800D2590_jp();
// void func_800D25D0_jp();
// void func_800D287C_jp();
// void func_800D289C_jp();
// void func_800D2AA0_jp();
// void func_800D2AD0_jp();
// void func_800D2B94_jp();
// void func_800D2BEC_jp();

extern Audiomgr* audiomgr_class_p;
extern Audiomgr audiomgr_class;
extern s32 B_80144FB8_jp;



#endif

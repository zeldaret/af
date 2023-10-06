#ifndef AC_SET_MANAGER_H
#define AC_SET_MANAGER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "libc/stddef.h"
#include "segment_symbols.h"

struct Game_Play;
struct Set_Manager;

typedef s32 (*SetManagerOvlProc)(struct Set_Manager*, struct Game_Play*);
typedef s32 (*SetManagerMoveProc)(struct Game_Play*, struct Set_Manager*);

#define SETMGR_OVERLAY_BUFFER_SIZE 0x4000

#define SETMGR_TIMER 5

typedef struct SetMgrPlayerPos {
    /* 0x00 */ s32 nextBx;
    /* 0x04 */ s32 nextBz;
    /* 0x08 */ s32 curBx;
    /* 0x0C */ s32 curBz;
    /* 0x10 */ s32 prevBx;
    /* 0x14 */ s32 prevBz;
} SetMgrPlayerPos;

typedef struct SetMgrKeep {
    /* 0x148 */ u8 unk_0[0x148];
} SetMgrKeep; // size = 0x148

typedef struct SetMgrOvl {
  /* 0x0000 */ u8 buf[SETMGR_OVERLAY_BUFFER_SIZE];
  /* 0x4000 */ SetManagerOvlProc ovlProc;
} SetMgrOvl; // size = 0x4004
 
#define SETMGR_OVERLAY(name, proc1, proc2) \
    { SEGMENT_ROM_START(name), SEGMENT_ROM_END(name), proc1, SEGMENT_VRAM_END(name), proc2, }

typedef struct SetMgrOvlInfo {
    /* 0x00 */ RomOffset vromStart;
    /* 0x04 */ RomOffset vromEnd;
    /* 0x08 */ void* vramStart;
    /* 0x0C */ void* vramEnd;
    /* 0x10 */ void* ovlTypeEnd;
} SetMgrOvlInfo; // size = 0x14

typedef struct Set_Manager {
  /* 0x0000 */ Actor actor;
  /* 0x0174 */ u8 moveProc;
  /* 0x0175 */ u8 nextMove;
  /* 0x0176 */ u8 setOvlType;
  /* 0x0178 */ SetMgrOvl setOverlay;
  /* 0x417C */ s32 unk_417C;
  /* 0x4180 */ SetMgrPlayerPos playerPos;
  /* 0x4198 */ SetMgrKeep keep;
  /* 0x42E0 */ s16 timer;
  /* 0x42E4 */ s32 unk_42E4;
} Set_Manager; // size = 0x42E8

typedef enum SetMgrOverlayType {
    /* 0 */ SETMGR_OVERLAY_START,
    /* 0 */ SETMGR_OVERLAY_INSECT = SETMGR_OVERLAY_START,
    /* 1 */ SETMGR_OVERLAY_GYOEI,
    /* 2 */ SETMGR_OVERLAY_MAX,
} SetMgrOverlayType; 

typedef enum SetMgrMoveProcType {
    /* 0 */ SETMGR_MOVE_CHECK_SET,
    /* 1 */ SETMGR_MOVE_CHECK_WAIT,
    /* 2 */ SETMGR_MOVE_SET,
    /* 3 */ SETMGR_MOVE_MAX,
} SetMgrMoveProcType;


#endif

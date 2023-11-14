#ifndef AC_TOOLS_H
#define AC_TOOLS_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;

typedef enum ToolName {
    /* 0x00 */ TOOL_UMBRELLA0,
    /* 0x01 */ TOOL_UMBRELLA1,
    /* 0x02 */ TOOL_UMBRELLA2,
    /* 0x03 */ TOOL_UMBRELLA3,
    /* 0x04 */ TOOL_UMBRELLA4,
    /* 0x05 */ TOOL_UMBRELLA5,
    /* 0x06 */ TOOL_UMBRELLA6,
    /* 0x07 */ TOOL_UMBRELLA7,
    /* 0x08 */ TOOL_UMBRELLA8,
    /* 0x09 */ TOOL_UMBRELLA9,
    /* 0x0A */ TOOL_UMBRELLA10,
    /* 0x0B */ TOOL_UMBRELLA11,
    /* 0x0C */ TOOL_UMBRELLA12,
    /* 0x0D */ TOOL_UMBRELLA13,
    /* 0x0E */ TOOL_UMBRELLA14,
    /* 0x0F */ TOOL_UMBRELLA15,
    /* 0x10 */ TOOL_UMBRELLA16,
    /* 0x11 */ TOOL_UMBRELLA17,
    /* 0x12 */ TOOL_UMBRELLA18,
    /* 0x13 */ TOOL_UMBRELLA19,
    /* 0x14 */ TOOL_UMBRELLA20,
    /* 0x15 */ TOOL_UMBRELLA21,
    /* 0x16 */ TOOL_UMBRELLA22,
    /* 0x17 */ TOOL_UMBRELLA23,
    /* 0x18 */ TOOL_UMBRELLA24,
    /* 0x19 */ TOOL_UMBRELLA25,
    /* 0x1A */ TOOL_UMBRELLA26,
    /* 0x1B */ TOOL_UMBRELLA27,
    /* 0x1C */ TOOL_UMBRELLA28,
    /* 0x1D */ TOOL_UMBRELLA29,
    /* 0x1E */ TOOL_UMBRELLA30,
    /* 0x1F */ TOOL_UMBRELLA31,
    /* 0x20 */ TOOL_KEITAI,
    /* 0x21 */ TOOL_UTIWA,
    /* 0x22 */ TOOL_HANABI,
    /* 0x23 */ TOOL_CRACKER,
    /* 0x24 */ TOOL_PISTOL,
    /* 0x25 */ TOOL_FLAG,
    /* 0x26 */ TOOL_TUMBLER,
    /* 0x27 */ TOOL_NPC_SAO,
    /* 0x28 */ TOOL_TAMA1,
    /* 0x29 */ TOOL_TAMA2,
    /* 0x2A */ TOOL_TAMA3,
    /* 0x2B */ TOOL_TAMA4
} ToolName;

typedef struct ToolActor {
    /* 0x000 */ Actor actor;
    /* 0x174 */ ToolName toolName;
    /* 0x178 */ MtxF unk178;
    /* 0x1B8 */ UNK_TYPE unk1B8;
    /* 0x1BC */ UNK_TYPE unk1BC; // process index
} ToolActor; // size >= 0x1C0

typedef ToolActor* (*ToolBirthProc)(ToolName, s32, ToolActor*, struct Game_Play*, s16, s32*);
typedef s32 (*ToolChgRequestModeProc)(Actor*, ToolActor*, s32);

typedef struct ToolClip {
    /* 0x00 */ ToolBirthProc aTOL_birth_proc;
    /* 0x04 */ ToolChgRequestModeProc aTOL_chg_request_mode_proc;
    /* 0x08 */ u32 umbrellaObjectIndex;
} ToolClip; // size >= 0xC

#endif

#ifndef AC_STRUCTURE_H
#define AC_STRUCTURE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "c_keyframe.h"

struct Game_Play;
struct Structure;
struct Game;

typedef void (*StructureActionFunc)(struct Structure*, struct Game_Play*);

typedef struct Structure {
    /* 0x000 */ Actor actor;
    /* 0x174 */ s32 unk174;
    /* 0x178 */ SkeletonInfoR skeletonInfo;
    /* 0x1E8 */ s32 unk1E8;
    /* 0x1EC */ Vec3s jointTable[15];
    /* 0x246 */ Vec3s morphTable[15];
    /* 0x2A0 */ StructureActionFunc unk2A0;
    /* 0x2A4 */ UNK_TYPE1 unk2A4[0x10];
    /* 0x2B4 */ UNK_TYPE unk2B4;
    /* 0x2B8 */ UNK_TYPE1 unk2B8[0x4];
    /* 0x2BC */ UNK_TYPE unk2BC;
    /* 0x2C0 */ UNK_TYPE1 unk2C0[0x8];
    /* 0x2C8 */ f32 unk2C8;
    /* 0x2CC */ f32 unk2CC;
    /* 0x2D0 */ f32 unk2D0;
    /* 0x2D4 */ UNK_TYPE1 unk2D4[0x4];
} Structure; // size = 0x2D8

typedef Structure* (*aSTR_setupActor_proc)(struct Game* game, u16 actorName, s16, f32, f32);
typedef void (*aSTR_get_overlay_area_proc)(struct ActorOverlay*, size_t);
typedef void (*aSTR_free_overlay_area_proc )(void);
typedef Structure* (*aSTR_get_actor_area_proc)(void);
typedef void (*aSTR_free_actor_area_proc)(Structure* structure);
typedef UNK_RET (*actorStructureClip_unkA8)(UNK_PTR, UNK_TYPE, u16 name, Structure* structure);
typedef UNK_RET (*actorStructureClip_unkAC)(u16 structureName);
typedef UNK_RET (*aSTR_get_pal_segment)(u16 structurePaletteName);

typedef struct StructureClip {
    /* 0x000 */ aSTR_setupActor_proc setupActorProc;
    /* 0x004 */ aSTR_get_overlay_area_proc getOverlayProc;
    /* 0x008 */ aSTR_free_overlay_area_proc freeOverlayAreaProc;
    /* 0x00C */ aSTR_get_actor_area_proc getActorAreaProc;
    /* 0x010 */ aSTR_free_actor_area_proc freeActorAreaProc;
    /* 0x014 */ UNK_TYPE1 unk_14[0x94];
    /* 0x0A8 */ actorStructureClip_unkA8 unk_A8; //unload object
    /* 0x0AC */ actorStructureClip_unkAC unk_AC; //load object
    /* 0x0B0 */ UNK_TYPE unk_B0;
    /* 0x0B4 */ UNK_TYPE1 pad[0x450-0xb4];
    /* 0x450 */ aSTR_get_pal_segment getPalSegment;
    /* 0x454 */ UNK_TYPE unk_454;
    /* 0x458 */ UNK_TYPE1 pad2[0x86C-0x458];
    /* 0x86C */ UNK_TYPE unk_86C;
} StructureClip; // size = 0x870

typedef enum StructureName {
    /* 0x045 */ STRUCTURE_TOUDAI = 45
} StructureName; // size = 

typedef enum StructurePaletteName {
    /* 0x090 */ STRUCTURE_TOUDAI_PAL = 90
} StructurePaletteName; // size = 

#endif

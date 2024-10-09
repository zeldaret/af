#include "ac_arrange_room.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_common_data.h"
#include "segment_symbols.h"
#include "m_rcp.h"

void Arrange_Room_Actor_ct(Actor* actor, Game_Play* play);
void Arrange_Room_Actor_dt(Actor* actor, Game_Play* game_play);
void Arrange_Room_Actor_move(Actor* thisx, Game_Play* game_play);
void Arrange_Room_Actor_draw(Actor* actor, Game_Play* play);
void aAR_Redma();

ActorProfile Arrange_Room_Profile = {
    /* */ ACTOR_ARRANGE_ROOM,
    /* */ ACTOR_PART_5,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x8006,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Arrange_Room),
    /* */ Arrange_Room_Actor_ct,
    /* */ Arrange_Room_Actor_dt,
    /* */ Arrange_Room_Actor_move,
    /* */ Arrange_Room_Actor_draw,
    /* */ NULL,
};

extern Gfx rom_myhome2_floor_model[];
extern Gfx rom_myhome2_wall_model[];
extern Gfx rom_myhome2_wall_modelT[];

#define AR_WALL_ROOM_SIZE 0x1020
#define AR_FLOOR_ROOM_SIZE 0x2020

#define AR_TEXTURE_SIZE 0x800

void* aAR_SecureDmaRam(Game_Play* play, s32 size) {
    s32 id = 0;
    u8* segment;
    s32 num = play->objectExchangeBank.num;

    if (mSc_secure_exchange_keep_bank(&play->objectExchangeBank, id, ALIGN8(size))) {
        segment = play->objectExchangeBank.status[num].segment;
        return segment;
    } else {
        return NULL;
    }
}

// refactored to mRmTp_CopyWallData, name unknown

void aAR_CopyWallData(void* vram, s32 idx) {
    if (vram != NULL) {
        DmaMgr_RequestSyncDebug(vram, SEGMENT_ROM_START(object_0182A000) + (AR_WALL_ROOM_SIZE * idx), AR_WALL_ROOM_SIZE,
                                "../ac_arrange_room.c", 169);
    }
}

// refactored to mRmTp_CopyFloorData, name unknown

void aAR_CopyFloorData(void* vram, s32 idx) {
    if (vram != NULL) {
        DmaMgr_RequestSyncDebug(vram, SEGMENT_ROM_START(object_017A1000) + (AR_FLOOR_ROOM_SIZE * idx),
                                AR_FLOOR_ROOM_SIZE, "../ac_arrange_room.c", 190);
    }
}

void aAR_SetClip(Actor* actor, s32 flag) {
    Arrange_Room* arrangeRoom = (Arrange_Room*)actor;

    if (flag != FALSE) {
        arrangeRoom->clip.arrangeRoomActor = arrangeRoom;
        arrangeRoom->clip.proc = aAR_Redma;
        common_data.clip.arrangeRoomClip = &arrangeRoom->clip;
    } else {
        common_data.clip.arrangeRoomClip = NULL;
    }
}

void Arrange_Room_Actor_ct(Actor* actor, Game_Play* play) {
    Arrange_Room* arrangeRoom = (Arrange_Room*)actor;
    s16 wallFloorIdx;
    s16 wallIdx;
    s16 floorIdx;
    UNUSED s32 pad;

    mNpc_RenewalNpcRoom(&wallFloorIdx);
    actor->params = wallFloorIdx;
    aAR_SetClip(actor, TRUE);
    wallIdx = (wallFloorIdx >> 8) & 0xFF;
    floorIdx = (u8)wallFloorIdx;

    if (floorIdx < 0) {
        floorIdx = 0;
    } else if (floorIdx >= 0x40) {
        floorIdx = 0x3F;
    }

    if (wallIdx < 0) {
        wallIdx = 0;
    } else if (wallIdx >= 0x40) {
        wallIdx = 0x3F;
    }

    arrangeRoom->vram = NULL;
    arrangeRoom->wallDataPtr = NULL;
    arrangeRoom->wallIdx = wallIdx;
    arrangeRoom->floorDataPtr = NULL;
    arrangeRoom->floorIdx = floorIdx;

    {
        s32 size;
        size = SEGMENT_ROM_SIZE(segment_013E7000);
        size = ALIGN8(size);
        arrangeRoom->vram = aAR_SecureDmaRam(play, size);

        if (arrangeRoom->vram != NULL) {
            DmaMgr_RequestSyncDebug(arrangeRoom->vram, SEGMENT_ROM_START(segment_013E7000), size,
                                    "../ac_arrange_room.c", 332);
        }
    }

    arrangeRoom->wallDataPtr = aAR_SecureDmaRam(play, AR_WALL_ROOM_SIZE);

    if (arrangeRoom->wallDataPtr != NULL) {
        aAR_CopyWallData(arrangeRoom->wallDataPtr, arrangeRoom->wallIdx);
    }

    arrangeRoom->floorDataPtr = aAR_SecureDmaRam(play, AR_FLOOR_ROOM_SIZE);

    if (arrangeRoom->floorDataPtr != NULL) {
        aAR_CopyFloorData(arrangeRoom->floorDataPtr, arrangeRoom->floorIdx);
    }
}

void Arrange_Room_Actor_dt(Actor* actor, UNUSED Game_Play* play) {
    aAR_SetClip(actor, FALSE);
}

void aAR_DrawFloor(Actor* actor, Game_Play* play) {
    u8* ptr;
    UNUSED u8* ptr2;
    UNUSED u8* ptr3;
    UNUSED u8* ptr4;
    UNUSED u8* ptr5;
    Arrange_Room* arrangeRoom = (Arrange_Room*)actor;
    UNUSED s32 pad;

    ptr = arrangeRoom->floorDataPtr;
    _texture_z_light_fog_prim(play->state.gfxCtx);

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_translate(0.0f, 0.0f, 0.0f, 0);
    Matrix_scale(0.05f, 0.05f, 0.05f, 1);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_6, arrangeRoom->vram);
    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_C, ptr);
    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_8, ptr + (0x20 + (AR_TEXTURE_SIZE * 0)));
    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_9, ptr + (0x20 + (AR_TEXTURE_SIZE * 1)));
    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_A, ptr + (0x20 + (AR_TEXTURE_SIZE * 2)));
    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_B, ptr + (0x20 + (AR_TEXTURE_SIZE * 3)));
    gSPDisplayList(POLY_OPA_DISP++, rom_myhome2_floor_model);

    CLOSE_DISPS(graph);
}

void aAR_DrawWall(Actor* actor, Game_Play* play) {
    Arrange_Room* arrangeRoom = (Arrange_Room*)actor;
    u8* ptr;
    UNUSED u8* ptr2;
    UNUSED u8* ptr3;
    UNUSED s32 pad;

    ptr = arrangeRoom->wallDataPtr;

    _texture_z_light_fog_prim(play->state.gfxCtx);

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_translate(0.0f, 0.0f, 0.0f, 0);
    Matrix_scale(0.05f, 0.05f, 0.05f, 1);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_6, arrangeRoom->vram);
    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_8, ptr + (0x20 + (AR_TEXTURE_SIZE * 0)));
    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_9, ptr + (0x20 + (AR_TEXTURE_SIZE * 1)));
    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_A, ptr);

    gSPDisplayList(POLY_OPA_DISP++, rom_myhome2_wall_model);
    gSPDisplayList(POLY_OPA_DISP++, rom_myhome2_wall_modelT);

    CLOSE_DISPS(play->state.gfxCtx);
}

void Arrange_Room_Actor_draw(Actor* actor, Game_Play* play) {
    Global_kankyo_set_room_prim(play);
    aAR_DrawFloor(actor, play);
    aAR_DrawWall(actor, play);
}

void Arrange_Room_Actor_move(UNUSED Actor* actor, UNUSED Game_Play* play) {
}

void aAR_Redma() {
    Arrange_Room* arrangeRoom = common_data.clip.arrangeRoomClip->arrangeRoomActor;

    if (arrangeRoom != NULL) {
        u32 start = SEGMENT_ROM_START(segment_013E7000);
        s32 size = ALIGN8(SEGMENT_ROM_SIZE(segment_013E7000));

        DmaMgr_RequestSyncDebug(arrangeRoom->vram, start, size, "../ac_arrange_room.c", 545);
        aAR_CopyWallData(arrangeRoom->wallDataPtr, arrangeRoom->wallIdx);
        aAR_CopyFloorData(arrangeRoom->floorDataPtr, arrangeRoom->floorIdx);
    }
}

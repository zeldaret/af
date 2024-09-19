#include "global.h"
#include "ac_goza.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "m_player_lib.h"
#include "m_field_info.h"
#include "69E2C0.h"

#define THIS ((Goza*)thisx)

void aGOZ_actor_ct(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_dt(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_init(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_draw(Actor* thisx, Game_Play* game_play);
void aGOZ_set_bgOffset(Goza* this, s32 processIndex);
void aGOZ_setup_action(Goza* this, s32 processIndex);

#if 0
ActorProfile Goza_Profile = {
    /* */ ACTOR_GOZA,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x582A,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Goza),
    /* */ aGOZ_actor_ct,
    /* */ aGOZ_actor_dt,
    /* */ aGOZ_actor_init,
    /* */ aGOZ_actor_draw,
    /* */ NULL,
};
#endif

void aGOZ_actor_ct(Actor* thisx, Game_Play* game_play UNUSED) {
    Goza* this = THIS;
    
    aGOZ_setup_action(this, 0);
    aGOZ_set_bgOffset(this, 1);
}

void aGOZ_actor_dt(Actor* thisx, Game_Play* game_play UNUSED) {
    Goza* this = THIS;
    
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->objectSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable),
                                                       STRUCTURE_TYPE_GOZA, &this->structureActor.actor);
    
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->paletteSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable),
                                                       STRUCTURE_PALETTE_GOZA, &this->structureActor.actor);
    
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->shadowSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable),
                                                       STRUCTURE_TYPE_GOZA, &this->structureActor.actor);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/aGOZ_set_bgOffset.s")

void aGOZ_wait(Goza* this UNUSED, Game_Play* game_play UNUSED) {
}

extern GozaActionFunc D_80A76820_jp[];

void aGOZ_setup_action(Goza* this, s32 processIndex) {
    // TODO: replace extern above with commented out code
    // static GozaActionFunc process[] = { aGOZ_wait };

    // this->structureActor.process = process[processIndex];
    this->structureActor.process = D_80A76820_jp[processIndex];
}

void aGOZ_actor_move(Actor* thisx, Game_Play* game_play) {
    Goza* this = THIS;
    StructureActor* goza = &this->structureActor;
    Player* player = get_player_actor_withoutCheck(game_play);
    s32 gozaBlockX;
    s32 gozaBlockZ;
    s32 playerBlockX;
    s32 playerBlockZ;
    
    mFI_Wpos2BlockNum(&gozaBlockX, &gozaBlockZ, goza->actor.world.pos);
    mFI_Wpos2BlockNum(&playerBlockX, &playerBlockZ, player->actor.world.pos);
    
    if ((mDemo_Check(1, &player->actor) == 0) && (mDemo_Check(5, &player->actor) == 0) &&
        ((gozaBlockX != playerBlockX) || (gozaBlockZ != playerBlockZ))) {
        Actor_delete(&goza->actor);
    } else {
        ((GozaActionFunc)goza->process)(this, game_play);
    }
}

void aGOZ_actor_init(Actor *thisx, Game_Play *game_play) {
    Goza* this = THIS;
    StructureActor* goza = &this->structureActor;
    
    mFI_SetFG_common(0xF0F4, goza->actor.home.pos, FALSE);
    aGOZ_actor_move(&goza->actor, game_play);
    goza->actor.update = aGOZ_actor_move;
}
/* Warning: struct struct_8085E9B0 is not defined (only forward-declared) */
/* Warning: struct SceneDmaStatus is not defined (only forward-declared) */

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/aGOZ_actor_draw.s")

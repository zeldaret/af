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
void func_80A76208_jp(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_init(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Goza_Profile = {
    /* */ ACTOR_GOZA,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x582A,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Goza),
    /* */ aGOZ_actor_ct,
    /* */ func_80A76208_jp,
    /* */ aGOZ_actor_init,
    /* */ aGOZ_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/aGOZ_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/func_80A76208_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/func_80A76294_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/func_80A76494_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/func_80A764A4_jp.s")

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
    
    mFI_SetFG_common(0xF0F4, this->structureActor.actor.home.pos, FALSE);
    aGOZ_actor_move(&this->structureActor.actor, game_play);
    this->structureActor.actor.update = aGOZ_actor_move;
}
/* Warning: struct struct_8085E9B0 is not defined (only forward-declared) */
/* Warning: struct SceneDmaStatus is not defined (only forward-declared) */

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/aGOZ_actor_draw.s")

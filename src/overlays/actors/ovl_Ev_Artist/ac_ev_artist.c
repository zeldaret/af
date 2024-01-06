#include "ac_ev_artist.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEART_actor_ct(Actor* thisx, Game_Play* game_play);
void aEART_actor_dt(Actor* thisx, Game_Play* game_play);
void aEART_actor_init(Actor* thisx, Game_Play* game_play);
void aEART_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Ev_Artist_Profile = {
    /* */ ACTOR_EV_ARTIST,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Artist),
    /* */ aEART_actor_ct,
    /* */ aEART_actor_dt,
    /* */ aEART_actor_init,
    /* */ (void*)none_proc1,
    /* */ aEART_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/aEART_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/aEART_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/aEART_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/aEART_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D6CF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D6D90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D6DF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D6EA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D6EF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D6F24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D7028_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D70BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D7154_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D7190_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D71C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D71F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D7234_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D7324_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D7354_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D7384_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D73C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D73F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D7454_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D74AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Artist/ac_ev_artist/func_809D74D8_jp.s")

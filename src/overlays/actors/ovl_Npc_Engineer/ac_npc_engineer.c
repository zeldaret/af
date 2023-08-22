#include "ac_npc_engineer.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "include/unknown_structs.h"

void aNEG_actor_ct(Actor* thisx, Game_Play* game_play);
void aNEG_actor_dt();
void aNEG_actor_init();
void aNEG_actor_save();

#if 0
ActorProfile Npc_Engineer_Profile = {
    /* */ ACTOR_NPC_ENGINEER,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Engineer),
    /* */ aNEG_actor_ct,
    /* */ aNEG_actor_dt,
    /* */ aNEG_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNEG_actor_save,
};
#endif

//#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/aNEG_actor_ct.s")
extern struct_809AEFA4 D_809AEFA4_jp;

void aNEG_actor_ct(Actor* thisx, Game_Play* game_play) {
    Npc_Engineer* this = (Npc_Engineer*)thisx;
    if (common_data.unk_1004C->unk_BC(thisx, game_play) == 1) {
        this->unk7C0 = none_proc1;
        common_data.unk_1004C->unk_C0(this, game_play, &D_809AEFA4_jp);
        this->unk80C = -1;
        this->unk7FD = 0;
        this->unk8AC = -1;
        this->actor.colStatus.mass = 0xFE;
        this->actor.shape.rot.y = 0x4000;
        this->actor.world.rot.y = 0x4000;
        this->unk8DC = 0x4000;
        this->unk7D4 = 4;
        this->unk7D5 = 0;
        this->unk7D6 = 0;
    }
}
//#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/aNEG_actor_save.s")
void aNEG_actor_save() {
    common_data.unk_1004C->unk_C8();
}
//#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/aNEG_actor_dt.s")
void aNEG_actor_dt() {
    common_data.unk_1004C->unk_C4();
}
//#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/aNEG_actor_init.s")
void aNEG_actor_init() {
    common_data.unk_1004C->unk_CC();
}
//#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/func_809AEF28_jp.s")
void func_809AEF28_jp(void) {
    common_data.unk_1004C->unk_D0();
}
//#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Engineer/ac_npc_engineer/func_809AEF54_jp.s")
void func_809AEF54_jp(void) {
    common_data.unk_1004C->unk_E4();
}

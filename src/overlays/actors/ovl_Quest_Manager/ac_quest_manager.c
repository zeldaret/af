#include "ac_quest_manager.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aQMgr_actor_ct(Actor* thisx, Game_Play* game_play);
void aQMgr_actor_dt(Actor* thisx, Game_Play* game_play);
void aQMgr_actor_move_main(Actor* thisx, Game_Play* game_play);
void aQMgr_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Quest_Manager_Profile = {
    /* */ ACTOR_QUEST_MANAGER,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Quest_Manager),
    /* */ aQMgr_actor_ct,
    /* */ aQMgr_actor_dt,
    /* */ aQMgr_actor_move_main,
    /* */ (ActorFunc)none_proc1,
    /* */ aQMgr_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80954D80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80954E0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80954E90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80954F5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80954FE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955060_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955150_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809551C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955224_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955264_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809552E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955344_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809553C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955408_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955468_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955658_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955668_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_8095573C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955814_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955940_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955990_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955AAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955B14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955B6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955BC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955BFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955C14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955CA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955D4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955D8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955DD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955E38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955E60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955E88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955F08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955F38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80955FA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956028_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_8095613C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_8095619C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809561D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809561F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956248_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956278_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956314_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_8095639C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956424_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809564C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809564F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956568_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_8095658C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956614_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956638_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956668_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809566F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956730_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956750_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809567C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956800_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956840_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_8095687C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809568A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809568CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_809568F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956974_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956A24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956AC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956B58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956C48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956C98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956E4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956EA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/func_80956EC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/aQMgr_actor_move_main.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/aQMgr_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/aQMgr_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Quest_Manager/ac_quest_manager/aQMgr_actor_save.s")

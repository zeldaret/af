#include "ac_event_manager.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEvMgr_ct(Actor* thisx, Game_Play* game_play);
void aEvMgr_dt(Actor* thisx, Game_Play* game_play);
void aEvMgr_move(Actor* thisx, Game_Play* game_play);
void aEvMgr_draw(Actor* thisx, Game_Play* game_play);
void aEvMgr_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Event_Manager_Profile = {
    /* */ ACTOR_EVENT_MANAGER,
    /* */ ACTOR_PART_0,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Event_Manager),
    /* */ aEvMgr_ct,
    /* */ aEvMgr_dt,
    /* */ aEvMgr_move,
    /* */ aEvMgr_draw,
    /* */ aEvMgr_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095B8B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095B96C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095B9CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095BA60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095BB80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095BBFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095BC60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/aEvMgr_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/aEvMgr_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095BD28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/aEvMgr_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/aEvMgr_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/aEvMgr_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095BDE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095C09C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095C264_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095C2C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095C2DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095C2F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095C2FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095C37C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095C4A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095C6C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095C994_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095CC88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095CD98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095CF90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095D1E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095D280_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095D324_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095D524_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095D608_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095D6F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095D818_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095D940_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095DA20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095DAD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095DC64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095DDE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095DFF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095E130_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095E2A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095E404_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095E49C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095E4CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095E534_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095E5B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095E63C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095EC24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095EDE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095EE1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095EE90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095EEF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095EF30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095EF94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F054_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F0C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F100_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F114_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F1D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F240_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F280_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F330_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F3A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F404_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F444_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F4A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F50C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F578_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F58C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F5A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F5B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F60C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F66C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F680_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F758_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F7B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F834_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F884_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F8C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F928_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F998_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095F9E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FA28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FABC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FB30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FB70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FBD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FC68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FCDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FD1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FD80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FE70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FEFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8095FF3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_8096002C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_809600C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_809601AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960240_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960280_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960370_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960404_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_809604F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960580_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_809605C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_809606B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960700_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960740_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960808_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960858_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960978_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_809609C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960AB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960B28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960C28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960CCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960D50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960DBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960E18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960E2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960E40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960F38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80960FC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80961004_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80961100_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80961274_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_809612B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80961380_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80961654_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_80961768_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Event_Manager/ac_event_manager/func_809618A4_jp.s")

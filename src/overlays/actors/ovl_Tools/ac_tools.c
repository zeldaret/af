#include "ac_tools.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTOL_actor_ct(Actor* thisx, PlayState* play);
void aTOL_actor_dt(Actor* thisx, PlayState* play);

#if 0
ActorProfile Tools_Profile = {
    /* */ ACTOR_TOOLS,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tools),
    /* */ aTOL_actor_ct,
    /* */ aTOL_actor_dt,
    /* */ (ActorFunc)none_proc1,
    /* */ (ActorFunc)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tools/ac_tools/aTOL_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tools/ac_tools/aTOL_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tools/ac_tools/func_809657EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tools/ac_tools/func_8096595C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tools/ac_tools/func_80965A4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tools/ac_tools/func_80965A70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tools/ac_tools/func_80965ACC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tools/ac_tools/func_80965B20_jp.s")

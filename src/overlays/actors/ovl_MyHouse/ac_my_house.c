#include "ac_my_house.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_collision_bg.h"

void func_80A05D50_jp(Actor* thisx, Game_Play* game_play);
void func_80A05F88_jp(Actor* thisx, Game_Play* game_play);
void func_80A06DF0_jp(Actor* thisx, Game_Play* game_play);
void func_80A071A0_jp(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile MyHouse_Profile = {
    /* */ ACTOR_MY_HOUSE,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5800,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(MyHouse),
    /* */ func_80A05D50_jp,
    /* */ func_80A05F88_jp,
    /* */ func_80A06DF0_jp,
    /* */ func_80A071A0_jp,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A05D50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A05F88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06068_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06098_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A0612C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A061BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06284_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A063B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A064E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A0664C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A0668C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A066B4_jp.s")

extern s8 D_80A07510_jp[];

void aMHS_make_bgOffset(mCoBG_unkStruct2* arg0, s8 arg1, s32 arg2) {
    s32 var_v0;
    s32 i;

    var_v0 = (arg2 == 0) ? 0 : 0x60;

    for (i = 0; i != 16; i++, arg0++) {
        arg0->unk0 = 0x64;
        arg0->unk1 = (D_80A07510_jp[var_v0 + i * 6 + 0] != 0xB) ? D_80A07510_jp[var_v0 + i * 6 + 0] : arg1;
        arg0->unk2 = (D_80A07510_jp[var_v0 + i * 6 + 1] != 0xB) ? D_80A07510_jp[var_v0 + i * 6 + 1] : arg1;
        arg0->unk3 = (D_80A07510_jp[var_v0 + i * 6 + 2] != 0xB) ? D_80A07510_jp[var_v0 + i * 6 + 2] : arg1;
        arg0->unk4 = (D_80A07510_jp[var_v0 + i * 6 + 3] != 0xB) ? D_80A07510_jp[var_v0 + i * 6 + 3] : arg1;
        arg0->unk5 = (D_80A07510_jp[var_v0 + i * 6 + 4] != 0xB) ? D_80A07510_jp[var_v0 + i * 6 + 4] : arg1;
        arg0->unk6 = D_80A07510_jp[var_v0 + i * 6 + 5];
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A068AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06A58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06AF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06B74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06BE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06CD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06CF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06DF0_jp.s")

// aMHS_actor_draw_before
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06E64_jp.s")

// aMHS_actor_draw_after
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A07008_jp.s")

// aMHS_actor_draw
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A071A0_jp.s")

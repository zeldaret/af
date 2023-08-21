#include "m_submenu.h"
#include "m_common_data.h"
#include "m_lib.h"
#include "fault.h"
#include "ovlmgr.h"
#include "attributes.h"
#include "libc/stdint.h"

extern UNK_TYPE D_8010DCE0_jp;
extern UNK_TYPE D_8010DCE4_jp;

extern SubmenuArea* SubmenuArea_visit;
extern SubmenuArea SubmenuArea_dlftbl[];

typedef void (*fnptr_8010DD24)(Game_Play1CBC*);

extern fnptr_8010DD24 D_8010DD24_jp[];

extern FaultClient B_80144670_jp;
extern FaultAddrConvClient B_80144680_jp;

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/RO_STR_80117920_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/RO_STR_8011792C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4420_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4440_jp.s")

void SubmenuArea_DoLink(SubmenuArea* area, Game_Play1CBC* arg1, s32 arg2) {
    size_t var_t0;
    s32 var_t1;
    size_t temp_v0;

    area->allocatedRamAddr = D_8010DCE0_jp;
    if (arg2 == 1) {
        temp_v0 = (((uintptr_t)area->vramEnd - (uintptr_t)area->vramStart) + 0xF) & ~0xF;
        if ((u32) D_8010DCE4_jp >= temp_v0) {
            var_t0 = D_8010DCE4_jp - temp_v0;
            var_t1 = D_8010DCE0_jp + temp_v0;
        } else {
            var_t0 = 0;
            var_t1 = 0;
        }
        ovlmgr_LoadImpl(area->vromStart, area->vromEnd, area->vramStart, area->vramEnd, area->allocatedRamAddr, var_t1, var_t0);
    } else {
        ovlmgr_Load(area->vromStart, area->vromEnd, area->vramStart, area->vramEnd, area->allocatedRamAddr);
    }

    area->unk_14 = (uintptr_t)area->allocatedRamAddr - (uintptr_t)area->vramStart;
    SubmenuArea_visit = area;
    arg1->unk_24 = area->allocatedRamAddr;
    arg1->unk_28 = (s32) ((uintptr_t)area->allocatedRamAddr + ((((uintptr_t)area->vramEnd - (uintptr_t)area->vramStart) + 0x3F) & ~0x3F));
}

void SubmenuArea_DoUnlink(SubmenuArea* area, Game_Play1CBC* arg1) {
    if (area->allocatedRamAddr == NULL) {
        return;
    }

    arg1->unk_24 = area->allocatedRamAddr;
    arg1->unk_28 = area->allocatedRamAddr;
    area->unk_14 = 0;
    bzero(area->allocatedRamAddr, (uintptr_t)area->vramEnd - (uintptr_t)area->vramStart);
    area->allocatedRamAddr = NULL;
    SubmenuArea_visit = NULL;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C46AC_jp.s")

#if 0
void* mSM_ovlptr_dllcnv(void* vram, Game_Play1CBC* arg1) {
    SubmenuArea* var_v1;

    var_v1 = SubmenuArea_visit;
    if (var_v1 == 0) {
        var_v1 = &SubmenuArea_dlftbl;
        if (func_800C46AC_jp(&SubmenuArea_dlftbl, arg1) == 0) {
            return NULL;
        }
    }

    if ((var_v1 == 0) || ((u32) vram < (u32) var_v1->unk_0C) || ((u32) vram >= (u32) var_v1->unk_10)) {
        return NULL;
    }
    return (uintptr_t)vram + var_v1->unk_14;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_ovlptr_dllcnv.s")
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C47B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C497C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C49D4_jp.s")

void mSM_submenu_ovlptr_cleanup(Game_Play1CBC* arg0) {
    Fault_RemoveClient(&B_80144670_jp);
    Fault_RemoveAddrConvClient(&B_80144680_jp);
    if (SubmenuArea_visit != NULL) {
        SubmenuArea_DoUnlink(SubmenuArea_visit, arg0);
        SubmenuArea_visit = NULL;
    }

    // One of those two is SubmenuArea_allocp
    D_8010DCE0_jp = 0;
    D_8010DCE4_jp = 0;
}

void load_player(Game_Play1CBC* arg0) {
    SubmenuArea* playerActorOvl = &SubmenuArea_dlftbl[1];

    if (SubmenuArea_visit == playerActorOvl) {
        return;
    }

    if (SubmenuArea_visit != NULL) {
        SubmenuArea_DoUnlink(SubmenuArea_visit, arg0);
    }

    SubmenuArea_DoLink(playerActorOvl, arg0, 1);
}

void mSM_submenu_ct(Game_Play1CBC* arg0) {
    bzero(arg0, sizeof(Game_Play1CBC));

    arg0->unk_0C = 0;
    arg0->unk_20 = 0;

    if (common_data.unk_104AD == 1) {
        arg0->unk_E2 = 1;
        common_data.unk_104AD = 0;
    }

    arg0->unk_30 = none_proc1;
    arg0->unk_34 = none_proc1;
}

void mSM_submenu_dt(UNUSED Game_Play1CBC* arg0) {

}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4D8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4DB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4DD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4DFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4E2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_submenu_ctrl.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C50C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C50EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C510C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5228_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C524C_jp.s")

void mSM_submenu_move(Game_Play1CBC* arg0) {
    D_8010DD24_jp[arg0->unk_0C](arg0);
}

#if 0
extern UNK_TYPE SubmenuArea_dlftbl;
extern UNK_TYPE* SubmenuArea_visit;

void mSM_submenu_draw(Game_Play1CBC* arg0) {
    if ((arg0->unk_00 >= 3) && (arg0->unk_0C == 3) && (&SubmenuArea_dlftbl == SubmenuArea_visit)) {
        arg0->unk_34();
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_submenu_draw.s")
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C53B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C543C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C54A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C54F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C557C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C55E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5640_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C56AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5798_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C582C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C58B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C592C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5984_jp.s")

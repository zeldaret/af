#include "m_trademark.h"
#include "m_actor.h"
#include "m_common_data.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_npc.h"
#include "m_view.h"
#include "sys_math.h"
#include "sys_matrix.h"
#include "libc64/qrand.h"
#include "z_std_dma.h"
#include "67E840.h"
#include "69CB30.h"
#include "6B3DC0.h"
#include "6B8F20.h"
#include "6BFE60.h"
#include "6DE300.h"
#include "6DB420.h"
#include "6E0F50.h"
#include "6EC9E0.h"
#include "6EDD10.h"
#include "6F5550.h"
#include "segment_symbols.h"
#include "macros.h"

#include "overlays/gamestates/ovl_play/m_play.h"

#if 0
D_80805B20_jp
D_80805B34_jp
D_80805B48_jp
D_80805B5C_jp
D_80805B70_jp
#endif

extern demo_door_data* l_demo_door_data_table[];

extern UNK_TYPE demo_npc_list;
extern s32 demo_npc_num;

typedef struct struct_80805CB4 {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ u8 unk_1;
    /* 0x2 */ u8 unk_2;
    /* 0x0 */ UNK_TYPE1 unk_3[0x1];
    /* 0x4 */ s16 unk_4;
} struct_80805CB4; // size = 0x6

extern struct_80805CB4 D_80805CB4_jp[];

#if 0
D_80805CD8_jp
D_80805ED8_jp
D_808060D8_jp
D_80806158_jp
D_80806338_jp
D_80806458_jp
D_808065D8_jp
#endif

extern UNK_TYPE D_808075D8_jp;

extern UNK_TYPE D_80807908_jp;

#if 0
D_80808000_jp
#endif

extern Lightsn D_80808508_jp;

extern u8 D_80808520_jp[];



extern UNK_TYPE B_80808560_jp;
extern UNK_TYPE B_80818560_jp;
extern UNK_TYPE B_80828560_jp;
extern OSMesgQueue B_80828620_jp[6];
extern UNK_TYPE B_808286B0_jp;


s32 func_80804C40_jp(void) {
    OSMesgQueue* var_s1 = B_80828620_jp;
    s32 var_s0;

    if (func_80090120_jp() != 0) {
        return 1;
    }

    for (var_s0 = 0; var_s0 < ARRAY_COUNT(B_80828620_jp); var_s0++, var_s1++) {
        if (osRecvMesg(var_s1, NULL, OS_MESG_NOBLOCK) == 0) {
            return 0;
        }
    }

    func_80090130_jp(1);
    return 1;
}

s32 set_npc_4_title_demo(Game_Trademark* this) {
    mNpc_SetAnimalTitleDemo(&demo_npc_list, common_data.animals, this);
    mNpc_SetNpcList(common_data.npclist, common_data.animals, demo_npc_num, 0);

    return demo_npc_num;
}

void mTM_demotime_set(s32 arg0) {

    common_data.time.rtc_enabled = 0;
    common_data.time.rtc_time.year = 0x7D1;
    common_data.time.rtc_time.min = 0;

    if (arg0 != 0) {
        struct_80805CB4* temp_v0 = &D_80805CB4_jp[arg0-1];

        common_data.time.rtc_time.month = temp_v0->unk_0;
        common_data.time.rtc_time.day = temp_v0->unk_1;
        common_data.time.rtc_time.hour = temp_v0->unk_2;
        common_data.unk_1056C = temp_v0->unk_4;
    }
}

void trademark_goto_demo_scene(Game_Trademark* this) {
    s32 temp_v0;

    mCPk_InitPak(0);
    common_data.now_private = common_data.private;

    if (mFRm_CheckSaveData() == 0) {
        Private_c* var_s0;
        s32 var_s1;

        // TODO: make a substruct
        bzero(&common_data, 0x10000);
        mFRm_ClearSaveCheckData(&common_data);

        var_s0 = common_data.private;
        for (var_s1 = 0; var_s1 < ARRAY_COUNT(common_data.private); var_s1++) {
            mPr_ClearPrivateInfo(var_s0);
            var_s0++;
        }

        common_data.land_info.unk_6 = 1;
        common_data.house_owner_name = 0xFFFF;
        common_data.last_field_id = 0xFFFF;
    }

    mEv_ClearEventInfo();
    temp_v0 = mEv_CheckTitleDemo();
    if (temp_v0 > 0) {
        demo_door_data* doorData = l_demo_door_data_table[temp_v0-1];

        common_data.unk_10754 = *doorData;
        common_data.unk_10754.unk_00 = doorData->unk_00 + 1;

        mTM_demotime_set(temp_v0);
        mPr_RandomSetPlayerData_title_demo();
        set_npc_4_title_demo(this);
        common_data.unk_1014B = 3;
    }

    common_data.unk_00014 = 0x21;
    mTM_set_season();
    common_data.unk_104AD = 1;

    STOP_GAMESTATE(&this->state);
    SET_NEXT_GAMESTATE(&this->state, play_init, sizeof(Game_Play));
}

void func_80804EE0_jp(Game_Trademark* this, f32 arg1, f32 arg2, f32 arg3) {
    Vec3f sp34;
    Vec3f sp28;
    Vec3f sp1C;

    sp34.x = arg1;
    sp34.y = arg2;
    sp34.z = arg3;
    sp1C.z = 0.0f;
    sp1C.y = 1.0f;
    sp1C.x = 0.0f;
    sp28.z = 0.0f;
    sp28.y = 0.0f;
    sp28.x = 0.0f;
    setPerspectiveView(&this->view, 15.0f, 10.0f, 12800.0f);
    setLookAtView(&this->view, &sp34, &sp28, &sp1C);
    showView(&this->view, 0xF);
}

void func_80804F78_jp(Game_Trademark* this) {
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fv0;
    s16 temp_a2; // sp22
    s16 temp_a1; // sp20

    temp_a2 = this->unk_25A6A;
    this->unk_25A6A = temp_a2 + this->unk_25A6C;
    temp_a1 = this->unk_25A6A;

    temp_fv1 = sinf_table(temp_a1 * 0.0000958738f) * this->unk_00214;

    if (this->unk_25A6F == 0) {
        var_fa0 = temp_fv1 * 3.0f;
        var_fv0 = temp_fv1;
    } else {
        var_fv0 = 1.0f - temp_fv1;
        var_fa0 = 1.0f + temp_fv1;
    }

    this->unk_00208 = var_fv0;
    this->unk_0020C = var_fa0;
    this->unk_00210 = var_fv0;

    if ((this->unk_25A6F == 0) && (temp_a1 >= 0x4000)) {
        this->unk_25A6F = 1;
    }

    if ((!this->unk_25A6C) && (!this->unk_25A6C)) {}

    if (((temp_a2 < 0) && (temp_a1 >= 0)) || ((temp_a2 < -0x8000) && (temp_a1 >= -0x8000))) {
        this->unk_00214 *= 0.3f;
        this->unk_25A6C = this->unk_25A6C + 0xC00;
    }

    if (ABS(this->unk_00214) < 0.02f) {
        if (this->unk_25A6E == 1) {
            this->unk_25A6E = 2;
        }
        this->unk_00208 = 1.0f;
        this->unk_0020C = 1.0f;
        this->unk_00210 = 1.0f;
    }
}

void func_80805104_jp(Game_Trademark* this) {
    UNUSED s32 pad[2];
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;
    GraphicsContext* temp_s0;
    f32 sp44;
    f32 sp40;

    temp_s0 = this->state.gfxCtx;
    OPEN_DISPS(temp_s0);

    func_80804F78_jp(this);

    sp64.x = 69.0f;
    sp64.y = 69.0f;
    sp64.z = 69.0f;

    sp4C.x = -4949.148f;
    sp4C.y = 4002.5417f;
    sp4C.z = 1119.0837f;

    sp58.x = 0.0f;
    sp58.y = 0.0f;
    sp58.z = 0.0f;
    HiliteReflect_init(&sp58, &sp4C, &sp64, temp_s0);

    gSPSetLights1(POLY_OPA_DISP++, D_80808508_jp);

    func_80804EE0_jp(this, 0.0f, 500.0f, 1000.0f);
    _texture_z_light_fog_prim(temp_s0);

    do {
        sp40 = this->unk_00208 * 0.006f;
        sp44 = this->unk_0020C * 0.006f;
        Matrix_translate(0.0f, -15.0f, 0.0f, MTXMODE_NEW);

        Matrix_scale(sp40, sp44, sp40, 1);
        Matrix_RotateY(0x2000, MTXMODE_APPLY);
    } while (0);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(temp_s0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, &D_808075D8_jp);

    CLOSE_DISPS(temp_s0);
}

void nintendo_logo_move(Game_Trademark* this) {
    if (this->unk_25A6E == 2) {
        this->unk_25A66 += 0x10;
        if (this->unk_25A66 >= 0xFF) {
            this->unk_25A66 = 0xFF;
            this->unk_25A6E = 4;
        }
    } else if (this->unk_25A6E == 4) {
        if (DECR(this->unk_25A64) == 0) {
            this->unk_25A6E = 3;
        }
    }
}

void nintendo_logo_draw(Game_Trademark* this) {
    UNUSED s32 pad;
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    OPEN_DISPS(gfxCtx);

    nintendo_logo_move(this);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0xFF, 255, 255, 255, this->unk_25A66);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_THRESHOLD);
    gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_POINT);
    gDPSetCycleType(POLY_OPA_DISP++, G_CYC_1CYCLE);
    gSPClearGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT);
    gDPSetTexturePersp(POLY_OPA_DISP++, G_TP_NONE);
    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);
    gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_8b, 128, &D_80807908_jp);
    gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_8b, 16, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(POLY_OPA_DISP++);
    gDPLoadTile(POLY_OPA_DISP++, G_TX_LOADTILE, 0, 0, 0x01FC, 0x0060);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_8b, 16, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    gDPSetTileSize(POLY_OPA_DISP++, G_TX_RENDERTILE, 0, 0, 0x01FC, 0x0060);

    POLY_OPA_DISP = gfx_gSPTextureRectangle1(POLY_OPA_DISP, 0x19C, 0x288, 0x398, 0x2E8, 0, 0, 0, 0x400, 0x400);

    CLOSE_DISPS(gfxCtx);
}

void trademark_cancel(Game_Trademark* this) {
    if ((this->unk_25A70 == 0) && (this->unk_25A6E == 4)) {
        if (common_data.unk_10AB0 != 0) {
            if (CHECK_FLAG_ALL(CONTROLLER1(gamePT)->press.button, START_BUTTON)) {
                this->unk_25A70 = 1;
            }
        }
    }
}

void trademark_move(Game_Trademark* this) {
    if (this->unk_25A6E == 0) {
        if (DECR(this->unk_25A68) == 0) {
            mBGMPsComp_make_ps_lost_fanfare(D_80808520_jp[mTD_get_titledemo_no()], 0x168);
            func_800D1A9C_jp(0x105);
            this->unk_25A60 = 0;
            this->unk_25A6E = 1;
        }
    }

    if ((func_80804C40_jp() != 0) && ((this->unk_25A6E == 3) || (this->unk_25A70 != 0))) {
        if (this->unk_25A60 < 0xFF) {
            this->unk_25A60 += 8;
        }

        if (this->unk_25A71 != 1) {
            if (func_8008F768_jp(&B_80808560_jp, &B_80818560_jp) == 1) {
                this->unk_25A71 = 1;
            }
        }

        if ((this->unk_25A60 >= 0xFF) && (this->unk_25A71 == 1)) {
            this->unk_25A60 = 0xFF;
            this->unk_25A6E = 5;
        }
    }
}

void trademark_draw(Game_Trademark* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    UNUSED s32 pad;

    OPEN_DISPS(gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);

    DisplayList_initialize(gfxCtx, 0, 0, 0, NULL);

    if (this->unk_25A6E > 0) {
        func_80805104_jp(this);
    }

    if (this->unk_25A6E >= 2) {
        nintendo_logo_draw(this);
    }

    {
        Gfx* gfx = POLY_XLU_DISP;

        fade_black_draw(&gfx, this->unk_25A60);
        POLY_XLU_DISP = gfx;
    }

    CLOSE_DISPS(this->state.gfxCtx);
}

void trademark_main(Game* thisx) {
    Game_Trademark* this = (Game_Trademark*)thisx;
    GraphicsContext* gfxCtx;

    fqrand();

    trademark_cancel(this);
    trademark_move(this);
    trademark_draw(this);

    gfxCtx = this->state.gfxCtx;
    game_debug_draw_last(&this->state, gfxCtx);
    game_draw_last(gfxCtx);

    if (this->unk_25A6E == 5) {
        this->unk_25A6E = 0;
        trademark_goto_demo_scene(this);
    }
}

void trademark_cleanup(UNUSED Game* thisx) {
    mHm_hs_c* var_s0 = common_data.homes;
    s32 var_s1;

    for (var_s1 = 0; var_s1 != ARRAY_COUNT(common_data.homes); var_s1++, var_s0++) {
        var_s0->unk_024 = var_s1;
        mMl_clear_mail_box(var_s0->unk_478, ARRAY_COUNT(var_s0->unk_478));
    }
}

void trademark_init(Game* thisx) {
    UNUSED s32 pad;
    Game_Trademark* this = (Game_Trademark*)thisx;
    GraphicsContext* sp2C = this->state.gfxCtx;

    common_data_reinit();

    this->state.main = trademark_main;
    this->state.destroy = trademark_cleanup;

    initView(&this->view, sp2C);
    new_Matrix(&this->state);

    this->unk_25A60 = 0xFF;
    this->unk_25A66 = 0;
    this->unk_25A64 = 0x3C;
    this->unk_25A68 = 0;
    this->unk_0025C = 0;
    this->unk_00218 = 0;
    this->unk_25A6E = 0;
    this->unk_00208 = 0.0f;
    this->unk_0020C = 0.0f;
    this->unk_00210 = 0.0f;
    this->unk_00214 = 0.5f;
    this->unk_25A6A = 0;
    this->unk_25A6C = 0x13D0;
    this->unk_25A6F = 0;
    this->unk_25A70 = 0;
    this->unk_25A71 = 0;

    SetGameFrame(1);
    common_data.player_no = 0;
    common_data.unk_10008 = 0;
    common_data.scene_from_title_demo = -1U;
    func_80095414_jp();
    mNpc_ClearInAnimal();
    mNpc_FirstClearGoodbyMail();
    func_800BB0E8_jp();
    func_8008FA50_jp();
    func_8008F210_jp();

    func_80026E10_jp(&this->unk_00260, SEGMENT_ROM_START(segment_01136000), SEGMENT_ROM_SIZE(segment_01136000), "../m_trademark.c", 1081);
    func_800924CC_jp(&B_80828560_jp, B_80828620_jp, &B_808286B0_jp);

    func_8005EAA0_jp(0);
    func_8007D91C_jp(func_800C8E08_jp());
}

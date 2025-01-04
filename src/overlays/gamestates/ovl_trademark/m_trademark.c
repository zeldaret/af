#include "m_trademark.h"

#include "prevent_bss_reordering.h"
#include "audio.h"
#include "m_actor.h"
#include "m_common_data.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_flashrom.h"
#include "m_mail.h"
#include "m_npc.h"
#include "m_scene_table.h"
#include "m_time.h"
#include "m_rcp.h"
#include "m_view.h"
#include "sys_math.h"
#include "sys_matrix.h"
#include "libc64/qrand.h"
#include "m_std_dma.h"
#include "m_bgm.h"
#include "m_cpk.h"
#include "6B3DC0.h"
#include "6B8F20.h"
#include "6EC9E0.h"
#include "segment_symbols.h"
#include "macros.h"

#include "overlays/gamestates/ovl_play/m_play.h"

typedef enum TrademarkState {
    /* 0 */ TRADEMARK_STATE_0,
    /* 1 */ TRADEMARK_STATE_1,
    /* 2 */ TRADEMARK_STATE_2,
    /* 3 */ TRADEMARK_STATE_3,
    /* 4 */ TRADEMARK_STATE_4,
    /* 5 */ TRADEMARK_STATE_5,
} TrademarkState;

DoorData demo_1_door_data = { SCENE_TITLE_DEMO, 4, 0, 0, { 0x884, 0xC8, 0x338 }, 0, 3, { 0, 0, 0 } };
DoorData demo_2_door_data = { SCENE_TITLE_DEMO, 4, 0, 0, { 0xC92, 0x28, 0xC02 }, 0, 3, { 0, 0, 0 } };
DoorData demo_3_door_data = { SCENE_TITLE_DEMO, 4, 0, 0, { 0x845, 0xA0, 0x5D0 }, 0, 3, { 0, 0, 0 } };
DoorData demo_4_door_data = { SCENE_TITLE_DEMO, 4, 0, 0, { 0xB53, 0xA0, 0x44D }, 0, 3, { 0, 0, 0 } };
DoorData demo_5_door_data = { SCENE_TITLE_DEMO, 4, 0, 0, { 0x62A, 0x28, 0x9A8 }, 0, 3, { 0, 0, 0 } };

DoorData* l_demo_door_data_table[] = {
    &demo_1_door_data, &demo_2_door_data, &demo_3_door_data, &demo_4_door_data, &demo_5_door_data,
};

u8 B_80808560_jp[0x10000];
u8 B_80818560_jp[0x10000];
u8 B_80828560_jp[0xC0];
OSMesgQueue B_80828620_jp[6];
u8 B_808286B0_jp[0x20];

s32 func_80804C40_jp(void) {
    OSMesgQueue* mq = B_80828620_jp;
    s32 i;

    if (func_80090120_jp() != 0) {
        return true;
    }

    for (i = 0; i < ARRAY_COUNT(B_80828620_jp); i++, mq++) {
        if (osRecvMesg(mq, NULL, OS_MESG_NOBLOCK) == 0) {
            return false;
        }
    }

    func_80090130_jp(1);
    return true;
}

DemoNpc demo_npc_list[] = {
    { 0xE000, 1, 2, 3, 7 },     { 0xE04C, 1, 2, 8, 0xB }, { 0xE0AD, 1, 4, 0xC, 0xB }, { 0xE048, 2, 3, 5, 6 },
    { 0xE0B9, 2, 3, 4, 0xC },   { 0xE06F, 3, 5, 0xB, 5 }, { 0xE0AA, 4, 3, 3, 0xC },   { 0xE08C, 4, 4, 3, 4 },
    { 0xE09B, 4, 4, 0xC, 0xD }, { 0xE0C2, 4, 6, 5, 6 },   { 0xE07D, 5, 2, 0xC, 4 },   { 0xE061, 5, 2, 9, 0xB },
    { 0xE0B6, 5, 4, 0xB, 4 },   { 0xE093, 5, 5, 5, 0xB },
};
s32 demo_npc_num = ARRAY_COUNT(demo_npc_list);

s32 set_npc_4_title_demo(Game_Trademark* this) {
    mNpc_SetAnimalTitleDemo(demo_npc_list, common_data.save.animals, &this->state);
    mNpc_SetNpcList(common_data.npclist, common_data.save.animals, demo_npc_num, 0);

    return demo_npc_num;
}

typedef struct TradeDayEntry {
    /* 0x0 */ u8 month;
    /* 0x1 */ u8 day;
    /* 0x2 */ u8 hour;
    /* 0x4 */ s16 weather;
} TradeDayEntry; // size = 0x6

void mTM_demotime_set(s32 arg0) {
    common_data.time.rtcEnabled = 0;
    common_data.time.rtcTime.year = mTM_MIN_YEAR;
    common_data.time.rtcTime.min = 0;

    if (arg0 != 0) {
        static TradeDayEntry tradeday_table[] = {
            { lbRTC_APRIL, 6, 13, 3 },    { lbRTC_JUNE, 16, 13, 1 },   { lbRTC_AUGUST, 1, 6, 0 },
            { lbRTC_NOVEMBER, 1, 16, 0 }, { lbRTC_FEBRUARY, 1, 2, 2 }, { 0, 0, 0, 0 },
        };

        TradeDayEntry* temp_v0 = &tradeday_table[arg0 - 1];

        common_data.time.rtcTime.month = temp_v0->month;
        common_data.time.rtcTime.day = temp_v0->day;
        common_data.time.rtcTime.hour = temp_v0->hour;
        common_data.weather = temp_v0->weather;
    }
}

void trademark_goto_demo_scene(Game_Trademark* this) {
    s32 temp_v0;

    mCPk_InitPak(0);
    common_data.privateInfo = &common_data.save.saveFilePrivateInfo[0];

    if (mFRm_CheckSaveData() == 0) {
        PrivateInfo* privateInfo;
        s32 i;

        bzero(&common_data.save, sizeof(Save));
        mFRm_ClearSaveCheckData(&common_data);

        privateInfo = &common_data.save.saveFilePrivateInfo[0];
        for (i = 0; i < ARRAY_COUNT(common_data.save.saveFilePrivateInfo); i++) {
            mPr_ClearPrivateInfo(privateInfo);
            privateInfo++;
        }

        common_data.save.landInfo.exists = true;
        common_data.houseOwnerName = 0xFFFF;
        common_data.lastFieldId = 0xFFFF;
    }

    mEv_ClearEventInfo();
    temp_v0 = mEv_CheckTitleDemo();
    if (temp_v0 > 0) {
        DoorData* doorData = l_demo_door_data_table[temp_v0 - 1];

        common_data.doorData = *doorData;
        common_data.doorData.nextSceneId = doorData->nextSceneId + 1;

        mTM_demotime_set(temp_v0);
        mPr_RandomSetPlayerData_title_demo();
        set_npc_4_title_demo(this);
        common_data.unk_1014B = 3;
    }

    common_data.save.sceneNo = SCENE_TITLE_DEMO;
    mTM_set_season();
    common_data.unk_104AD = 1;

    STOP_GAMESTATE(&this->state);
    SET_NEXT_GAMESTATE(&this->state, play_init, sizeof(Game_Play));
}

void func_80804EE0_jp(Game_Trademark* this, f32 eyeX, f32 eyeY, f32 eyeZ) {
    xyz_t eye;
    xyz_t at;
    xyz_t up;

    eye.x = eyeX;
    eye.y = eyeY;
    eye.z = eyeZ;
    up.z = 0.0f;
    up.y = 1.0f;
    up.x = 0.0f;
    at.z = 0.0f;
    at.y = 0.0f;
    at.x = 0.0f;
    setPerspectiveView(&this->view, 15.0f, 10.0f, 12800.0f);
    setLookAtView(&this->view, &eye, &at, &up);
    showView(&this->view, 0xF);
}

void func_80804F78_jp(Game_Trademark* this) {
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fv0;
    s16 temp_a2;
    s16 temp_a1;

    temp_a2 = this->unk_25A6A;
    this->unk_25A6A += this->unk_25A6C;
    temp_a1 = this->unk_25A6A;

    temp_fv1 = sinf_table(BINANG_TO_RAD(temp_a1)) * this->unk_00214;

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

    if (((temp_a2 < 0) && (temp_a1 >= 0)) || ((temp_a2 < -0x8000) && (temp_a1 >= -0x8000))) {
        this->unk_00214 *= 0.3f;
        this->unk_25A6C += 0xC00;
    }

    if (ABS(this->unk_00214) < 0.02f) {
        if (this->curState == TRADEMARK_STATE_1) {
            this->curState = TRADEMARK_STATE_2;
        }
        this->unk_00208 = 1.0f;
        this->unk_0020C = 1.0f;
        this->unk_00210 = 1.0f;
    }
}

Vtx D_80805CD8_jp[] = {
#include "assets/jp/overlays/gamestates/ovl_trademark/m_trademark/D_80805CD8_jp.vtx.inc.c"
};
Vtx D_80805ED8_jp[] = {
#include "assets/jp/overlays/gamestates/ovl_trademark/m_trademark/D_80805ED8_jp.vtx.inc.c"
};
Vtx D_808060D8_jp[] = {
#include "assets/jp/overlays/gamestates/ovl_trademark/m_trademark/D_808060D8_jp.vtx.inc.c"
};
Vtx D_80806158_jp[] = {
#include "assets/jp/overlays/gamestates/ovl_trademark/m_trademark/D_80806158_jp.vtx.inc.c"
};
Vtx D_80806338_jp[] = {
#include "assets/jp/overlays/gamestates/ovl_trademark/m_trademark/D_80806338_jp.vtx.inc.c"
};
Vtx D_80806458_jp[] = {
#include "assets/jp/overlays/gamestates/ovl_trademark/m_trademark/D_80806458_jp.vtx.inc.c"
};

u8 D_808065D8_jp[] = {
#include "assets/jp/overlays/gamestates/ovl_trademark/m_trademark/D_808065D8_jp.i8.inc.c"
};

Gfx D_808075D8_jp[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 0xFF, 255, 220, 90, 255),
    gsDPSetEnvColor(230, 180, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(D_808065D8_jp, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(D_80805CD8_jp, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 19, 17, 0),
    gsSP2Triangles(20, 21, 22, 0, 21, 23, 22, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 27, 25, 0),
    gsSP2Triangles(28, 29, 30, 0, 29, 31, 30, 0),
    gsDPPipeSync(),
    gsDPSetPrimColor(0, 0xFF, 60, 90, 220, 255),
    gsDPSetEnvColor(0, 0, 160, 255),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(D_808065D8_jp, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(D_80805ED8_jp, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 3, 5, 0, 2, 5, 7, 0),
    gsSP2Triangles(0, 2, 7, 0, 8, 9, 10, 0),
    gsSP2Triangles(8, 10, 11, 0, 12, 13, 14, 0),
    gsSP2Triangles(12, 14, 15, 0, 11, 16, 8, 0),
    gsSP2Triangles(15, 17, 12, 0, 18, 8, 16, 0),
    gsSP2Triangles(19, 12, 17, 0, 16, 20, 21, 0),
    gsSP2Triangles(16, 21, 18, 0, 17, 22, 23, 0),
    gsSP2Triangles(17, 23, 19, 0, 24, 25, 26, 0),
    gsSP2Triangles(25, 27, 26, 0, 28, 29, 27, 0),
    gsSP2Triangles(1, 30, 2, 0, 5, 2, 31, 0),
    gsSP1Triangle(6, 5, 31, 0),
    gsSPVertex(D_808060D8_jp, 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 3, 0, 5, 6, 3, 0),
    gsSP1Triangle(0, 7, 1, 0),
    gsDPPipeSync(),
    gsDPSetPrimColor(0, 0xFF, 30, 210, 90, 255),
    gsDPSetEnvColor(0, 160, 0, 255),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(D_808065D8_jp, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(D_80806158_jp, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(4, 8, 5, 0, 0, 9, 1, 0),
    gsSP2Triangles(10, 1, 9, 0, 11, 5, 8, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(11, 8, 20, 0, 11, 20, 21, 0),
    gsSP2Triangles(10, 9, 22, 0, 10, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 27, 26, 28, 0),
    gsSP1Triangle(29, 27, 28, 0),
    gsSPVertex(D_80806338_jp, 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 3, 0, 6, 4, 3, 0),
    gsSP2Triangles(7, 8, 1, 0, 0, 7, 1, 0),
    gsSP2Triangles(3, 1, 9, 0, 6, 3, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 11, 13, 12, 0),
    gsSP2Triangles(14, 15, 13, 0, 15, 16, 13, 0),
    gsSP1Triangle(10, 17, 11, 0),
    gsDPPipeSync(),
    gsDPSetPrimColor(0, 0xFF, 255, 100, 80, 255),
    gsDPSetEnvColor(180, 0, 0, 255),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(D_808065D8_jp, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(D_80806458_jp, 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
    gsSPEndDisplayList(),
};

u8 D_80807908_jp[] = {
#include "assets/jp/overlays/gamestates/ovl_trademark/m_trademark/D_80807908_jp.i8.inc.c"
};

Lights1 D_80808508_jp = {
    { { { 0x64, 0x64, 0x64 }, 0, { 0x64, 0x64, 0x64 }, 0 } },
    {
        {
            { { 0xFF, 0xFF, 0xFF }, 0, { 0xFF, 0xFF, 0xFF }, 0, { 0x45, 0x45, 0x45 }, 0 },
        },
    },
};

void func_80805104_jp(Game_Trademark* this) {
    UNUSED s32 pad[2];
    xyz_t lightDir;
    xyz_t object;
    xyz_t eye;
    GraphicsContext* gfxCtx;
    f32 y;
    f32 xz;

    gfxCtx = this->state.gfxCtx;
    OPEN_DISPS(gfxCtx);

    func_80804F78_jp(this);

    lightDir.x = 69.0f;
    lightDir.y = 69.0f;
    lightDir.z = 69.0f;

    eye.x = -4949.148f;
    eye.y = 4002.5417f;
    eye.z = 1119.0837f;

    object.x = 0.0f;
    object.y = 0.0f;
    object.z = 0.0f;
    HiliteReflect_init(&object, &eye, &lightDir, gfxCtx);

    gSPSetLights1(POLY_OPA_DISP++, D_80808508_jp);

    func_80804EE0_jp(this, 0.0f, 500.0f, 1000.0f);
    _texture_z_light_fog_prim(gfxCtx);

    do {
        xz = this->unk_00208 * 0.006f;
        y = this->unk_0020C * 0.006f;
        Matrix_translate(0.0f, -15.0f, 0.0f, MTXMODE_NEW);

        Matrix_scale(xz, y, xz, MTXMODE_APPLY);
        Matrix_RotateY(0x2000, MTXMODE_APPLY);
    } while (0);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_808075D8_jp);

    CLOSE_DISPS(gfxCtx);
}

void nintendo_logo_move(Game_Trademark* this) {
    if (this->curState == TRADEMARK_STATE_2) {
        this->alpha += 16;
        if (this->alpha >= 255) {
            this->alpha = 255;
            this->curState = TRADEMARK_STATE_4;
        }
    } else if (this->curState == TRADEMARK_STATE_4) {
        if (DECR(this->unk_25A64) == 0) {
            this->curState = TRADEMARK_STATE_3;
        }
    }
}

void nintendo_logo_draw(Game_Trademark* this) {
    UNUSED s32 pad;
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    OPEN_DISPS(gfxCtx);

    nintendo_logo_move(this);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0xFF, 255, 255, 255, this->alpha);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_THRESHOLD);
    gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_POINT);
    gDPSetCycleType(POLY_OPA_DISP++, G_CYC_1CYCLE);
    gSPClearGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                              G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0,
                      ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0,
                      ENVIRONMENT);
    gDPSetTexturePersp(POLY_OPA_DISP++, G_TP_NONE);
    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);

    gDPLoadTextureTile(POLY_OPA_DISP++, D_80807908_jp, G_IM_FMT_I, G_IM_SIZ_8b, 128, 24, 0, 0, 0x7F, 0x18, 0,
                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                       G_TX_NOLOD);

    POLY_OPA_DISP = gfx_gSPTextureRectangle1(POLY_OPA_DISP, 0x19C, 0x288, 0x398, 0x2E8, 0, 0, 0, 0x400, 0x400);

    CLOSE_DISPS(gfxCtx);
}

void trademark_cancel(Game_Trademark* this) {
    if (!this->unk_25A70 && (this->curState == TRADEMARK_STATE_4)) {
        if (common_data.unk_10AB0 != 0) {
            if (CHECK_FLAG_ALL(CONTROLLER1(gamePT)->press.button, START_BUTTON)) {
                this->unk_25A70 = true;
            }
        }
    }
}

u8 s_titlebgm[] = {
    0x53, 0x54, 0x55, 0x56, 0x57,
};

void trademark_move(Game_Trademark* this) {
    if (this->curState == TRADEMARK_STATE_0) {
        if (DECR(this->unk_25A68) == 0) {
            mBGMPsComp_make_ps_lost_fanfare(s_titlebgm[mTD_get_titledemo_no()], 0x168);
            sAdo_SysTrgStart(0x105);
            this->fadeColor = 0;
            this->curState = TRADEMARK_STATE_1;
        }
    }

    if (func_80804C40_jp() && ((this->curState == TRADEMARK_STATE_3) || this->unk_25A70)) {
        if (this->fadeColor < 255) {
            this->fadeColor += 8;
        }

        if (this->unk_25A71 != 1) {
            if (func_8008F768_jp(&B_80808560_jp, &B_80818560_jp) == 1) {
                this->unk_25A71 = 1;
            }
        }

        if ((this->fadeColor >= 255) && (this->unk_25A71 == 1)) {
            this->fadeColor = 255;
            this->curState = TRADEMARK_STATE_5;
        }
    }
}

void trademark_draw(Game_Trademark* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    UNUSED s32 pad;

    OPEN_DISPS(gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);

    DisplayList_initialize(gfxCtx, 0, 0, 0, NULL);

    if (this->curState >= TRADEMARK_STATE_1) {
        func_80805104_jp(this);
    }

    if (this->curState >= TRADEMARK_STATE_2) {
        nintendo_logo_draw(this);
    }

    {
        Gfx* gfx = POLY_XLU_DISP;

        fade_black_draw(&gfx, this->fadeColor);
        POLY_XLU_DISP = gfx;
    }

    CLOSE_DISPS(gfxCtx);
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

    if (this->curState == TRADEMARK_STATE_5) {
        this->curState = TRADEMARK_STATE_0;
        trademark_goto_demo_scene(this);
    }
}

void trademark_cleanup(UNUSED Game* thisx) {
    mHm_hs_c* homes = common_data.save.homes;
    s32 i;

    for (i = 0; i != ARRAY_COUNT(common_data.save.homes); i++, homes++) {
        homes->unk_024 = i;
        mMl_clear_mail_box(homes->mailbox, ARRAY_COUNT(homes->mailbox));
    }
}

void trademark_init(Game* thisx) {
    UNUSED s32 pad;
    Game_Trademark* this = (Game_Trademark*)thisx;
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    common_data_reinit();

    this->state.main = trademark_main;
    this->state.destroy = trademark_cleanup;

    initView(&this->view, gfxCtx);
    new_Matrix(&this->state);

    this->fadeColor = 255;
    this->alpha = 0;
    this->unk_25A64 = 60;
    this->unk_25A68 = 0;
    this->unk_0025C = 0;
    this->unk_00218 = 0;
    this->curState = TRADEMARK_STATE_0;
    this->unk_00208 = 0.0f;
    this->unk_0020C = 0.0f;
    this->unk_00210 = 0.0f;
    this->unk_00214 = 0.5f;
    this->unk_25A6A = 0;
    this->unk_25A6C = 0x13D0;
    this->unk_25A6F = 0;
    this->unk_25A70 = false;
    this->unk_25A71 = 0;

    SetGameFrame(1);
    common_data.playerNumber = 0;
    common_data.playerDataMode = 0;
    common_data.sceneFromTitleDemo = -1;
    func_80095414_jp();
    mNpc_ClearInAnimal();
    mNpc_FirstClearGoodbyMail();
    func_800BB0E8_jp();
    func_8008FA50_jp();
    func_8008F210_jp();

    DmaMgr_RequestSyncDebug(&this->unk_00260, SEGMENT_ROM_START(segment_01136000), SEGMENT_ROM_SIZE(segment_01136000),
                            "../m_trademark.c", 1081);
    func_800924CC_jp(&B_80828560_jp, B_80828620_jp, &B_808286B0_jp);

    mBGMPsComp_scene_mode(0);
    mEv_SetTitleDemo(mTD_demono_get());
}

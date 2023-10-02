#include "ef_lamp_light.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "m_field_info.h"
#include "overlays/gamestates/ovl_play/m_play.h"

#define THIS ((Lamp_Light*)thisx)

void Ef_Lamp_Light_actor_ct(Actor* thisx, Game_Play* game_play);
void Ef_Lamp_Light_actor_dt(Actor* thisx, Game_Play* game_play);
s32 func_80967644_jp(void);
s32 func_80967678_jp(Lamp_Light* this UNUSED);
s32 func_809676BC_jp(void);
void func_809676E4_jp(Lamp_Light* this);
void Ef_Lamp_Light_actor_move(Actor* thisx, Game_Play* game_play);

ActorProfile Lamp_Light_Profile = {
    /* */ ACTOR_LAMP_LIGHT,
    /* */ ACTOR_PART_6,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Lamp_Light),
    /* */ Ef_Lamp_Light_actor_ct,
    /* */ Ef_Lamp_Light_actor_dt,
    /* */ Ef_Lamp_Light_actor_move,
    /* */ (void*)none_proc1,
    /* */ NULL,
};
static s16 D_80967884_jp[4] = { 2, 2, 1, 0 };
static s16 D_8096788C_jp[4] = { 0x10, 0x10, 8, 0 };
static s16* D_80967894_jp[2] = { D_80967884_jp, D_8096788C_jp };
static s16 D_8096789C_jp[4] = { 0, 0, 0, 0 };
static s16 D_809678A4_jp[4] = { 0xC8, 0xC8, 0x96, 0 };
static s16* D_809678AC_jp[2] = { D_8096789C_jp, D_809678A4_jp };

void Ef_Lamp_Light_actor_ct(Actor* thisx, Game_Play* game_play) {
    s32 pad UNUSED;
    Lamp_Light* this = (Lamp_Light*)thisx;

    game_play->kankyo.unk_1C = &this->unk_178;
    Light_diffuse_ct(&this->unk_178, 0, 0x50, 0, (u8)0, (u8)0, (u8)0);
    this->unk_188 = Global_light_list_new(game_play, &game_play->glight, &this->unk_178);
}

void Ef_Lamp_Light_actor_dt(Actor* thisx, Game_Play* game_play) {
    Lamp_Light* this = (Lamp_Light*)thisx;

    game_play->kankyo.unk_1C = NULL;
    Global_light_list_delete(&game_play->glight, this->unk_188);
}

s32 func_80967644_jp(void) {
    s32 var_v1;
    s32 temp_v0;

    temp_v0 = common_data.time.nowSec;
    var_v1 = 0;
    if ((temp_v0 < 0x5460) || (temp_v0 >= 0xFD20)) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 func_80967678_jp(Lamp_Light* this UNUSED) {
    s32 var_v1;
    s32 temp_v0;

    temp_v0 = common_data.time.nowSec;
    var_v1 = ((temp_v0 >= 0xFD20) && (temp_v0 < 0x14370)) ? 1 : 0;
    return var_v1;
}

s32 func_809676BC_jp(void) {
    s32 var_v1;

    var_v1 = 1;
    if ((u8)common_data.unk_104AE[0] == 1) {
        var_v1 = 0;
    }
    return var_v1;
}

void func_809676E4_jp(Lamp_Light* this) {
    s32 var_v1 = 0;

    switch (common_data.unk_10001) {
        case 2:
        case 3:
            switch (mFI_GetFieldId()) {
                case 0x6000:
                case 0x6001:
                case 0x6002:
                case 0x6003:
                    var_v1 = func_80967678_jp(this);
                    break;

                case 0x5000:
                case 0x5001:
                    var_v1 = func_809676BC_jp();
                    break;

                default:
                    var_v1 = func_80967644_jp();
                    break;
            }
            break;

        case 1:
            var_v1 = func_80967678_jp(this);
            break;
    }

    this->unk_174 = var_v1;
}

void Ef_Lamp_Light_actor_move(Actor* thisx, Game_Play* game_play UNUSED) {
    Lamp_Light* this = (Lamp_Light*)thisx;
    s16* var_s1;
    s16* var_s2;
    s32 temp_v1;
    s32 var_s3;
    s16 sp3A;
    u8* var_s0;

    func_809676E4_jp(this);
    var_s0 = this->unk_178.lights.diffuse.color;
    temp_v1 = this->unk_174;
    var_s1 = D_80967894_jp[temp_v1];
    var_s2 = D_809678AC_jp[temp_v1];

    for (var_s3 = 0; var_s3 < 3; var_s3++, var_s1++, var_s2++, var_s0++) {
        sp3A = *var_s0;
        chase_s(&sp3A, *var_s2, *var_s1);
        *var_s0 = sp3A;
    }
}

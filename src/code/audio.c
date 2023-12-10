#include "audio.h"
#include "audio_load.h"
#include "683030.h"
#include "71A140.h"
#include "71FA20.h"
#include "720B20.h"
#include "7205C0.h"
#include "7206E0.h"
#include "game.h"
#include "m_lib.h"
#include "sys_math_atan.h"

s32 S_ongenpos_refuse_fg = 0;

void sAdo_Calc_MicPosition_common(f32* distanceVal, u16* angleVal, xyz_t* pos) {
    UNUSED s32 pad;
    xyz_t* cameraPos;
    f32 diff;
    xyz_t posDiff;
    s16 angle;

    cameraPos = Camera2_getMicPos_p((Game_Play*)gamePT);

    diff = pos->x - cameraPos->x;
    posDiff.x = diff;
    posDiff.z = pos->y - cameraPos->y;
    posDiff.y = pos->z - cameraPos->z;

    angle = atans_table(posDiff.y, posDiff.x);

    if (distanceVal != NULL) {
        *distanceVal = sqrtf((posDiff.x * posDiff.x) + (posDiff.z * posDiff.z) + (posDiff.y * posDiff.y));
    }
    if (angleVal != NULL) {
        *angleVal = angle;
    }
}

void sAdo_Calc_MicPosition_forTrig(f32* distanceVal, u16* angleVal, xyz_t* pos) {
    sAdo_Calc_MicPosition_common(distanceVal, angleVal, pos);
}

void sAdo_Calc_MicPosition_forLevel(f32* distanceVal, u16* angleVal, xyz_t* pos) {
    sAdo_Calc_MicPosition_common(distanceVal, angleVal, pos);
}

void sAdo_GameFrame(void) {
    Na_GameFrame();
}

void* func_800D19BC_jp(void) {
    return func_800F8984_jp();
}

void func_800D19DC_jp(void) {
    func_800F8B2C_jp();
}

void sAdo_BgmStart(u8 id) {
    Na_BgmStart(id);
}

void sAdo_BgmStop(u16 id) {
    Na_BgmStop(id);
}

void sAdo_BgmTrOn(u8 id) {
    Na_BgmTrOn(id);
}

void sAdo_BgmTrOff(u8 id) {
    Na_BgmTrOff(id);
}

void sAdo_SysTrgStart(u16 id) {
    Na_SysTrgStart(id);
}

void sAdo_PlyWalkSe(s32 arg0, xyz_t* pos) {
    f32 distanceVal;
    u16 angleVal;

    sAdo_Calc_MicPosition_forTrig(&distanceVal, &angleVal, pos);
    Na_PlyWalkSe(arg0, angleVal, distanceVal);
}

void sAdo_PlyWalkSeRoom(s32 arg0, xyz_t* pos) {
    f32 distanceVal;
    u16 angleVal;

    sAdo_Calc_MicPosition_forTrig(&distanceVal, &angleVal, pos);
    Na_PlyWalkSeRoom(arg0, angleVal, distanceVal);
}

void sAdo_NpcWalkSe(s32 arg0, xyz_t* pos) {
    f32 distanceVal;
    u16 angleVal;

    sAdo_Calc_MicPosition_forTrig(&distanceVal, &angleVal, pos);
    Na_NpcWalkSe(arg0, angleVal, distanceVal);
}

void sAdo_NpcWalkSeRoom(u16 arg0, xyz_t* pos) {
    f32 distanceVal;
    u16 angleVal;

    sAdo_Calc_MicPosition_forTrig(&distanceVal, &angleVal, pos);
    Na_NpcWalkSeRoom(arg0, angleVal, distanceVal);
}

void sAdo_PlayerStatusLevel(u8 arg0, f32 speed) {
    Na_PlayerStatusLevel(arg0, speed);
}

void sAdo_VoiceSe(u8 arg0, s16 arg1, u8 arg2) {
    Na_VoiceSe(arg0, arg1, arg2);
}

void sAdo_Inst(u8 num, u8* arg1) {
    Na_Inst(num, arg1);
}

void sAdo_MessageStatus(u8 status) {
    Na_MessageStatus(status);
}

void sAdo_MessageSpeed(u8 speed) {
    Na_MessageSpeed(speed);
}

u8 sAdo_MessageSpeedGet(void) {
    return Na_MessageSpeedGet();
}

void sAdo_SysLevStart(u8 id) {
    Na_SysLevStart(id);
}

void sAdo_SysLevStop(u8 id) {
    Na_SysLevStop(id);
}

void sAdo_OngenPos(s32 arg0, u8 arg1, xyz_t* pos) {
    f32 distanceVal;
    u16 angleVal;

    if (S_ongenpos_refuse_fg == 0) {
        sAdo_Calc_MicPosition_forLevel(&distanceVal, &angleVal, pos);
        Na_OngenPos(arg0, arg1, angleVal, distanceVal);
    }
}

void sAdo_OngenTrgStart(u16 id, xyz_t* pos) {
    f32 distanceVal;
    u16 angleVal;

    sAdo_Calc_MicPosition_forTrig(&distanceVal, &angleVal, pos);
    Na_OngenTrgStart(id, angleVal, distanceVal);
}

void sAdo_SetOutMode(u8 mode) {
    Na_SetOutMode(mode);
}

void sAdo_SetVoiceMode(u8 mode) {
    Na_SetVoiceMode(mode);
}

void sAdo_FloorTrgStart(u8 id, xyz_t* pos) {
    f32 distanceVal;
    u16 angleVal;

    sAdo_Calc_MicPosition_forTrig(&distanceVal, &angleVal, pos);
    Na_FloorTrgStart(id, angleVal, distanceVal);
}

void sAdo_RhythmStart(s32 arg0, s8 arg1, s8 arg2) {
    Na_RhythmStart(arg0, arg1, arg2);
}

void sAdo_RhythmStop(void) {
    Na_RhythmStop();
}

void sAdo_RhythmAllStop(void) {
    Na_RhythmAllStop();
}

void sAdo_FurnitureInst(s32 distance, u8 trackId, s32 arg2, xyz_t* pos) {
    f32 distanceVal;
    u16 angleVal;

    sAdo_Calc_MicPosition_common(&distanceVal, &angleVal, pos);
    Na_FurnitureInst(distance, trackId, arg2, angleVal, distanceVal);
}

void sAdo_Pause(u8 mode) {
    Na_Pause(mode);
}

f32 sAdo_get_rhythm_buffer(void) {
    return get_rhythm_buffer();
}

s16 sAdo_GetRhythmSubTrack(void) {
    return Na_GetRhythmSubTrack();
}

void sAdo_GetRhythmInfo(void* arg0) {
    Na_GetRhythmInfo(arg0);
}

void sAdo_SetRhythmInfo(void* arg0) {
    Na_SetRhythmInfo(arg0);
}

s32 sAdo_InstCountGet(void) {
    return Na_InstCountGet();
}

void sAdo_RhythmPos(s32 distance, u8 arg1, xyz_t* pos) {
    f32 distanceVal;
    u16 angleVal;

    sAdo_Calc_MicPosition_forLevel(&distanceVal, &angleVal, pos);
    Na_RhythmPos(distance, arg1, angleVal, distanceVal);
}

void sAdo_SpecChange(s32 spec) {
    Na_SpecChange(spec);
}

void sAdo_MDPlayerPos(xyz_t* pos, u16 arg1, u16 arg2, s32 arg3) {
    u16 angleVal;
    f32 distanceVal;

    sAdo_Calc_MicPosition_common(&distanceVal, &angleVal, pos);
    Na_MDPlayerPos(angleVal, distanceVal, arg1, arg2, arg3);
}

void sAdo_BGMVolume(f32 volume, u16 pan) {
    Na_BGMVolume(volume, pan);
}

void sAdo_BgmCrossfadeStart(u8 arg0) {
    Na_BgmCrossfadeStart(arg0);
}

void sAdo_SubGameStart(void) {
    Na_SubGameStart();
}

void sAdo_SubGameEnd(void) {
    Na_SubGameEnd();
}

s32 sAdo_SubGameOK(void) {
    return Na_SubGameOK();
}

void sAdo_Tenki(u8 mode) {
    Na_Tenki(mode);
}

void func_800D213C_jp(DmaHandler handler) {
    func_800EBF6C_jp(handler);
}

void sAdos_KishaStatusTrg(u8 state) {

    Na_KishaStatusTrg(state);
}

void sAdos_KishaStatusLevel(f32 arg0, s32 arg1, f32 arg2, u16 arg3, s32 arg4, f32 arg5, u16 arg6) {
    Na_KishaStatusLevel(arg0, arg1, arg3, arg2, arg4, arg6, arg5);
}

s32 func_800D21CC_jp(void* arg0) {
    return func_800FC920_jp(arg0);
}

void sAdos_GetStaffRollInfo(u16* arg0) {
    Na_GetStaffRollInfo(arg0);
}

void sAdos_TTKK_ARM(u8 arg0) {
    Na_TTKK_ARM(arg0);
}

void sAdo_OngenTrgStartSpeed(u16 num, xyz_t* pos, f32 speed) {
    f32 distanceVal;
    u16 angleVal;

    sAdo_Calc_MicPosition_forTrig(&distanceVal, &angleVal, pos);
    Na_OngenTrgStartSpeed(num, angleVal, distanceVal, speed);
}

void sAdo_TrgSeEcho(u8 idx) {
    Na_TrgSeEcho(idx);
}

void sAdo_LevSeEcho(u8 idx) {
    Na_LevSeEcho(idx);
}

void sAdo_BGMFilter(u8 arg0) {
    Na_BGMFilter(arg0);
}

void sAdo_BgmMuteClear(void) {
    Na_BgmMuteClear();
}

u8 sAdo_BgmFadeoutCheck(void) {
    return Na_BgmFadeoutCheck();
}

u8 sAdo_SeFadeoutCheck(void) {
    return Na_SeFadeoutCheck();
}

void sAdo_SeStart(UNUSED s32 arg0) {
}

void sAdo_SeStop(UNUSED s32 arg0) {
}

void sAdo_RoomType(u8 type) {
    Na_RoomType(type);
}

void sAdo_SoftReset(void) {
    Na_SoftReset();
}

u16 sAdo_Get_WalkLabel(s32 type) {
    u16 ret;
    switch (type) {
        case 0:
        case 1:
        case 2:
            if (common_data.time.season != WINTER) {
                ret = 0x201;
            } else {
                ret = 0x206;
            }
            break;

        case 4:
        case 5:
        case 6:
            ret = 0x202;
            break;

        case 7:
            ret = 0x203;
            break;

        case 23:
            ret = 0x204;
            break;

        case 9:
            ret = 0x205;
            break;

        case 22:
            ret = 0x208;
            break;

        case 11:
            ret = 0x209;
            break;

        default:
            ret = 0x202;
            break;
    }
    return ret;
}

s32 sAdo_Get_KokeruLabel(s32 type) {
    u16 label = sAdo_Get_WalkLabel(type);
    s32 ret;

    switch (label) {
        case 0x201:
            ret = 0xe;
            break;

        case 0x206:
            ret = 0x13;
            break;

        case 0x202:
            ret = 0xf;
            break;

        case 0x203:
            ret = 0x10;
            break;

        case 0x204:
            ret = 0x11;
            break;

        case 0x205:
            ret = 0x12;
            break;

        case 0x208:
            ret = 0x156;
            break;

        case 0x209:
            ret = 0x157;
            break;

        default:
            ret = 15;
            break;
    }
    return ret;
}

void sAdo_SceneMode(u8 mode) {
    Na_SceneMode(mode);
}

void sAdo_RoomIncectPos(s32 distance, u8 insectId, xyz_t* pos) {
    f32 positionVal;
    u16 angleVal;

    sAdo_Calc_MicPosition_forLevel(&positionVal, &angleVal, pos);
    Na_RoomIncectPos(distance, insectId, angleVal, positionVal);
}

void sAdo_FurnitureInstPos(s32 distance, xyz_t* pos) {
    f32 positionVal;
    u16 angleVal;

    sAdo_Calc_MicPosition_forLevel(&positionVal, &angleVal, pos);
    Na_FurnitureInstPos(distance, angleVal, positionVal);
}

void sAdo_Set_ongenpos_refuse_fg(s32 state) {
    S_ongenpos_refuse_fg = state;
}

s32 sAdo_GameframeEnd_Check(void) {
    s32 check = S_ongenpos_refuse_fg;
    return check;
}

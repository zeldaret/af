#include "unk.h"

s32 padD5D000[] = { 0x00000000, 0x00000000 };

u32 StructurePaletteAddresses[] = {
    0x06000008, // obj_s_house1_a_pal
    0x06000028, // obj_s_house1_b_pal
    0x06000048, // obj_s_house1_c_pal
    0x06000068, // obj_s_house1_d_pal
    0x06000088, // obj_s_house1_e_pal
    0x06000128, // obj_s_house2_a_pal
    0x06000108, // obj_s_house2_b_pal
    0x060000E8, // obj_s_house2_c_pal
    0x060000C8, // obj_s_house2_d_pal
    0x060000A8, // obj_s_house2_e_pal
    0x060001C8, // obj_s_house3_a_pal
    0x060001A8, // obj_s_house3_b_pal
    0x06000188, // obj_s_house3_c_pal
    0x06000168, // obj_s_house3_d_pal
    0x06000148, // obj_s_house3_e_pal
    0x06000268, // obj_s_house4_a_pal
    0x06000248, // obj_s_house4_b_pal
    0x06000228, // obj_s_house4_c_pal
    0x06000208, // obj_s_house4_d_pal
    0x060001E8, // obj_s_house4_e_pal
    0x06000308, // obj_s_house5_a_pal
    0x060002E8, // obj_s_house5_b_pal
    0x060002C8, // obj_s_house5_c_pal
    0x060002A8, // obj_s_house5_d_pal
    0x06000288, // obj_s_house5_e_pal
    0x06000648, //
    0x06000668, //
    0x060006A8, //
    0x06000688, //
    0x060006C8, //
    0x060006E8, //
    0x06000708, //
    0x06000728, //
    0x06000748, //
    0x06000768, //
    0x06000788, //
    0x060007A8, //
    0x06000948, //
    0x06000988, //
    0x060009C8, //
    0x06000A08, //
    0x06000A88, //
    0x06000AC8, //
    0x06000AE8, //
    0x06000B08, //
    0x06000B28, //
    0x06000B48, //
    0x06000C08, //
    0x06000C28, //
    0x06000C48, //
    0x06000C68, //
    0x06000C88, //
    0x06000D48, //
    0x06000D68, //
    0x06000D88, //
    0x06000DA8, //
    0x06000DC8, //
    0x06000E88, //
    0x06000EC8, //
    0x06000F08, //
    0x06000008, //
    0x06000008, //
    0x06000F48, //
    0x06001008, //
    0x06000A48, // obj_s_yamishop_pal
    0x06000F88, // obj_buggy_pal
    0x06000FC8, //
    0x06000FE8, // obj_w_kamakura_pal
    0x06001048, // obj_e_goza_pal
    0x06001068, //
    0x06001088, //
    0x060010A8, //
    0x060010A8, //
    0x060010C8, // obj_e_mikuji_pal
    0x060010E8, // obj_e_count_pal
    0x06001108, // obj_e_count02_pal
    0x06001128, // obj_e_kago_r_pal
    0x06001148, // obj_e_kago_w_pal
    0x06001168, //
    0x06001188, //
    0x060011A8, // obj_e_koinobori_a_pal
    0x060011C8, // obj_dump_pal
    0x06001288, // obj_w_windmill_a_pal
    0x060012A8, // obj_w_windmill_b_pal
    0x060012C8, // obj_w_windmill_c_pal
    0x060012E8, // obj_w_windmill_d_pal
    0x06001308, // obj_w_windmill_e_pal
    0x06001328, // obj_01_lotus_pal
    0x06001348, // obj_e_mikanbox_pal
    0x06001368, // obj_s_douzou_dai_pal
    0x060013A8, //
    0x06000328, // obj_w_house1_a_pal
    0x06000348, // obj_w_house1_b_pal
    0x06000368, // obj_w_house1_c_pal
    0x06000388, // obj_w_house1_d_pal
    0x060003A8, // obj_w_house1_e_pal
    0x06000448, // obj_w_house2_a_pal
    0x06000428, // obj_w_house2_b_pal
    0x06000408, // obj_w_house2_c_pal
    0x060003E8, // obj_w_house2_d_pal
    0x060003C8, // obj_w_house2_e_pal
    0x060004E8, //
    0x060004C8, //
    0x060004A8, //
    0x06000488, //
    0x06000468, //
    0x06000588, //
    0x06000568, //
    0x06000548, //
    0x06000528, //
    0x06000508, //
    0x06000628, //
    0x06000608, //
    0x060005E8, //
    0x060005C8, //
    0x060005A8, //
    0x060007C8, //
    0x060007E8, //
    0x06000828, //
    0x06000808, //
    0x06000848, //
    0x06000868, //
    0x06000888, //
    0x060008A8, //
    0x060008C8, //
    0x060008E8, //
    0x06000908, //
    0x06000928, //
    0x06000968, //
    0x060009A8, //
    0x060009E8, //
    0x06000A28, //
    0x06000AA8, //
    0x06000B68, //
    0x06000B88, //
    0x06000BA8, //
    0x06000BC8, //
    0x06000BE8, //
    0x06000CA8, //
    0x06000CE8, //
    0x06000D08, //
    0x06000CC8, //
    0x06000D28, //
    0x06000DE8, //
    0x06000E28, //
    0x06000E48, //
    0x06000E08, //
    0x06000E68, //
    0x06000EA8, //
    0x06000EE8, //
    0x06000F28, //
    0x06000008, //
    0x06000008, //
    0x06000F68, //
    0x06001028, //
    0x06000A68, // obj_w_yamishop_pal
    0x06000FA8, // obj_buggy_winter_pal
    0x06000FC8, //
    0x06000FE8, // obj_w_kamakura_pal
    0x06001048, // obj_e_goza_pal
    0x06001068, //
    0x06001088, //
    0x060010A8, //
    0x060010A8, //
    0x060010C8, // obj_e_mikuji_pal
    0x060010E8, // obj_e_count_pal
    0x06001108, // obj_e_count02_pal
    0x06001128, // obj_e_kago_r_pal
    0x06001148, // obj_e_kago_w_pal
    0x06001168, //
    0x06001188, //
    0x060011A8, // obj_e_koinobori_a_pal
    0x060011C8, // obj_dump_pal
    0x060011E8, // obj_s_windmill_a_pal
    0x06001208, // obj_s_windmill_b_pal
    0x06001228, // obj_s_windmill_c_pal
    0x06001248, // obj_s_windmill_d_pal
    0x06001268, // obj_s_windmill_e_pal
    0x06001328, // obj_01_lotus_pal
    0x06001348, // obj_e_mikanbox_pal
    0x06001388, // obj_w_douzou_pal
    0x060013C8, // obj_w_toudai_pal
};

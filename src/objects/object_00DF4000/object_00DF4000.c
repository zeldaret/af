#include "ultratypes.h"

s32 padDF4000[] = { 0x00000000, 0x00000000 };

u32 StructureObjectAddresses[] = {
    0x06023BB0, // obj_s_house1
    0x06026388, // obj_s_house2
    0x06028B18, // obj_s_house3
    0x0602B208, // obj_s_house4
    0x0602D838, // obj_s_house5
    0x0603C710, // obj_s_myhome1
    0x0603EEE0, // obj_s_myhome2
    0x060417D0, // obj_s_myhome3
    0x060583F0, //
    0x0605C470, //
    0x06060E38, //
    0x06065998, //
    0x0604FE50, //
    0x0606FE70, //
    0x06074698, //
    0x06078D48, //
    0x06080A90, //
    0x060834C0, //
    0x0604BC80, // obj_s_kouban
    0x06012AD0, //
    0x06013A60, //
    0x060556A0, //
    0x0606A560, //
    0x06000000, // obj_s_yamishop
    0x06003440, // obj_s_uranai
    0x06056180, //
    0x0601AA00, // obj_w_kamakura
    0x060149F0, // obj_e_goza
    0x060542D0, //
    0x06092A90, //
    0x060880B8, //
    0x06085A40, //
    0x06021EE0, // obj_e_mikuji
    0x06006830, // obj_e_count01
    0x06008C90, // obj_e_count02_cl
    0x06016A40, // obj_e_kago_r
    0x06018A38, // obj_e_kago_w
    0x0608C7A0, //
    0x0608A730, //
    0x0601CAE0, // obj_e_koinobori
    0x0600FEE0, // obj_s_dump
    0x0608E830, // obj_s_windmill
    0x0601F6F0, // obj_s_lotus
    0x06020FE0, // obj_e_mikanbox
    0x0600A420, // obj_s_douzou
    0x0607D240, // obj_s_toudai
    0x06026380, //
    0x06028B10, //
    0x0602B200, //
    0x0602D830, //
    0x06030138, //
    0x0603EED8, //
    0x060417C8, //
    0x060441E0, //
    0x0605A428, //
    0x0605E950, //
    0x060633E0, //
    0x06067F70, //
    0x06052070, //
    0x06072278, //
    0x060769D8, //
    0x0607AFB0, //
    0x060834B8, //
    0x06085A30, //
    0x0604DD78, //
    0x06013A58, //
    0x060149E8, //
    0x06055C08, //
    0x0606D1D8, //
    0x06001A18, //
    0x06004E30, //
    0x060583E0, //
    0x0601CAD8, //
    0x06016A38, //
    0x06055690, //
    0x06095478, //
    0x0608A728, //
    0x060880B0, //
    0x06023BA8, //
    0x06008C80, //
    0x0600A418, //
    0x06018A30, //
    0x0601A9F0, //
    0x0608E828, //
    0x0608C798, //
    0x0601F6E8, //
    0x060114D0, //
    0x06090960, //
    0x06020FD0, //
    0x06021ED8, //
    0x0600D178, //
    0x0607EE80, //
    0x06030140, // obj_w_house1
    0x06032910, // obj_w_house2
    0x060350A0, // obj_w_house3
    0x06037790, // obj_w_house4
    0x06039E00, // obj_w_house5
    0x060441E8, // obj_w_myhome1
    0x060469B8, // obj_w_myhome2
    0x06049268, // obj_w_myhome3
    0x0605A430, //
    0x0605E958, //
    0x060633E8, //
    0x06067F78, //
    0x06052078, //
    0x06072280, //
    0x060769E0, //
    0x0607AFB8, //
    0x06080A90, //
    0x060834C0, //
    0x0604DD80, // obj_w_kouban
    0x06012AD0, //
    0x06013A60, //
    0x06055C10, //
    0x0606D1E0, //
    0x06001A20, // obj_w_yamishop
    0x06004E38, // obj_w_uranai
    0x06056180, //
    0x0601AA00, // obj_w_kamakura
    0x060149F0, // obj_e_goza
    0x060542D0, //
    0x06092A90, //
    0x060880B8, //
    0x06085A40, //
    0x06021EE0, // obj_e_mikuji
    0x06006830, // obj_e_count01
    0x06008C90, // obj_e_count02_cl
    0x06016A40, // obj_e_kago_r
    0x06018A38, // obj_e_kago_w
    0x0608C7A0, //
    0x0608A730, //
    0x0601CAE0, // obj_e_koinobori
    0x060114D8, // obj_w_dump
    0x06090968, // obj_w_windmill_v
    0x0601F6F0, // obj_s_lotus
    0x06020FE0, // obj_e_mikanbox
    0x0600D180, // obj_w_douzou
    0x0607EE88, // obj_w_toudai
    0x06032908, //
    0x06035098, //
    0x06037788, //
    0x06039DF8, //
    0x0603C700, //
    0x060469B0, //
    0x06049260, //
    0x0604BC78, //
    0x0605C468, //
    0x06060E30, //
    0x06065990, //
    0x0606A550, //
    0x060542C8, //
    0x06074690, //
    0x06078D40, //
    0x0607D230, //
    0x060834B8, //
    0x06085A30, //
    0x0604FE48, //
    0x06013A58, //
    0x060149E8, //
    0x06056178, //
    0x0606FE60, //
    0x06003438, //
    0x06006828, //
    0x060583E0, //
    0x0601CAD8, //
    0x06016A38, //
    0x06055690, //
    0x06095478, //
    0x0608A728, //
    0x060880B0, //
    0x06023BA8, //
    0x06008C80, //
    0x0600A418, //
    0x06018A30, //
    0x0601A9F0, //
    0x0608E828, //
    0x0608C798, //
    0x0601F6E8, //
    0x06012AC8, //
    0x06092A80, //
    0x06020FD0, //
    0x06021ED8, //
    0x0600FED8, //
    0x06080A88, //
};

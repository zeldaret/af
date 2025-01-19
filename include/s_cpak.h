#ifndef S_CPAK_H
#define S_CPAK_H

#include "ultra64.h"

#include "m_cpak.h"

void func_800CD640_jp(OSPfsState* pfsState, u16* company_code, u32* game_code);
s32 func_800CD68C_jp(OSPfsInfo* pfsInfo, s32 channel);
s32 func_800CD730_jp(OSPfsInfo* pfsInfo);
UNK_RET func_800CD760_jp(OSPfsInfo* pfsInfo, UNK_TYPE arg1, u32 arg2, void* arg3);
UNK_RET func_800CD82C_jp(OSPfsInfo* pfsInfo, UNK_TYPE arg1, u32 arg2, void* arg3);
s32 func_800CD8F8_jp(OSPfsInfo* pfsInfo, OSPfsState* pfsState, size_t size);
s32 func_800CD990_jp(OSPfsInfo* pfsInfo, OSPfsState* pfsState);
s32 func_800CD9F0_jp(OSPfsInfo* pfsInfo, OSPfsState* pfsState);
u32 func_800CDA4C_jp(OSPfsInfo* pfsInfo, OSPfsState* pfsState);
UNK_RET func_800CDA90_jp(OSPfsInfo* pfsInfo, UNK_PTR, UNK_PTR);
UNK_RET func_800CDAD0_jp(OSPfsInfo* pfsInfo);

#endif

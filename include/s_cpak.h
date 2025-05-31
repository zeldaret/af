#ifndef S_CPAK_H
#define S_CPAK_H

#include "ultra64.h"

#include "m_cpak.h"

void sCPk_SetCode(OSPfsState* pfsState, u16* companyCode, u32* gameCode);
s32 sCPk_PakOpen(OSPfsInfo* pfsInfo, s32 channel);
s32 sCPk_PakFreeArea(OSPfsInfo* pfsInfo);
s32 sCPk_Save(OSPfsInfo* pfsInfo, s32 offset, s32 size, u8* buffer);
s32 sCPk_Load(OSPfsInfo* pfsInfo, s32 offset, s32 size, u8* buffer);
s32 sCPk_MakeFile(OSPfsInfo* pfsInfo, OSPfsState* pfsState, size_t size);
s32 sCPk_FileOpen(OSPfsInfo* pfsInfo, OSPfsState* pfsState);
s32 sCPk_DeleteFile(OSPfsInfo* pfsInfo, OSPfsState* pfsState);
u32 sCPk_FileState(OSPfsInfo* pfsInfo, OSPfsState* pfsState);
s32 sCPk_FileNum(OSPfsInfo* pfsInfo, s32* maxFiles, s32* filesUsed);
s32 sCPk_RepairID(OSPfsInfo* pfsInfo);

#endif

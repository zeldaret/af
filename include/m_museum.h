#ifndef M_MUSEUM_H
#define M_MUSEUM_H

#include "ultra64.h"

typedef struct MuseumRecord {
  u8 contacted:1; /* set to TRUE when the museum has contacted the player */
  u8 remailPending:1; /* set to TRUE when the museum has non-fossil letters pending */
  u8 sendInfoMail:1; /* if set to true, museum info mail will be sent */
  u8 storedFossils:5; /* number of stored fossils */
} MuseumRecord;

void mMsm_ClearRecord(MuseumRecord*);
// void func_800A3420_jp();
// void func_800A345C_jp();
// void func_800A34E8_jp();
// void func_800A35C8_jp();
// void func_800A3658_jp();
void mMsm_SendInformationMail(void);
// void func_800A3784_jp();
// void func_800A37D0_jp();
// void func_800A3810_jp();
// void func_800A3A5C_jp();
// void func_800A3B84_jp();
// void func_800A3C18_jp();
// void func_800A3CF0_jp();
// void func_800A3E34_jp();
// void func_800A3F70_jp();
// void func_800A3FB4_jp();
// void func_800A4184_jp();
// void func_800A41BC_jp();
// void func_800A4254_jp();
// void func_800A43C0_jp();

#endif

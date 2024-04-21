#ifndef M_SCENE_FTR_H
#define M_SCENE_FTR_H

#include "ultra64.h"
#include "other_types.h"

struct Game_Play;
struct ObjectExchangeBank;

void mScn_Dma2Bank(struct ObjectExchangeBank* exchange, s32 id, RomOffset vrom, size_t size);
void mScn_KeepMyRoomBankNew(struct ObjectExchangeBank* exchange, s16 id, size_t size);
void mScn_ObtainCarpetBank(struct Game_Play*);
s32 mScn_ObtainFurnitureBank(struct Game_Play* play, s32 bank);
void mScn_ObtainMyRoomBank(struct Game_Play*);

#endif

#ifndef GAMEALLOC_H
#define GAMEALLOC_H

#include "ultra64.h"
#include "unk.h"

typedef struct GameAllocEntry {
    /* 0x0 */ struct GameAllocEntry* next;
    /* 0x4 */ struct GameAllocEntry* prev;
    /* 0x8 */ size_t size;
    /* 0xC */ UNK_TYPE1 unk_0C[0x4];
} GameAllocEntry; // size = 0x10

typedef struct GameAlloc {
    /* 0x00 */ GameAllocEntry base;
    /* 0x10 */ GameAllocEntry* head;
} GameAlloc; // size = 0x14

void func_800D3720_jp(GameAlloc* this);
void* gamealloc_malloc(GameAlloc* this, size_t size);
void gamealloc_free(GameAlloc* this, void* ptr);
void gamealloc_cleanup(GameAlloc* this);
void gamealloc_init(GameAlloc* this);

#endif

#include "gamealloc.h"
#include "malloc.h"
#include "libc/stdint.h"

void func_800D3720_jp(GameAlloc* this) {
    GameAllocEntry* iter = this->base.next;

    while (&this->base != iter) {
        iter = iter->next;
    }
}

void* gamealloc_malloc(GameAlloc* this, size_t size) {
    GameAllocEntry* ptr = malloc(size + sizeof(GameAllocEntry));

    if (ptr != NULL) {
        ptr->size = size;
        ptr->prev = this->head;
        this->head->next = ptr;
        this->head = ptr;
        ptr->next = &this->base;
        this->base.prev = this->head;

        return ptr + 1;
    }

    return NULL;
}

void gamealloc_free(GameAlloc* this, void* ptr) {
    if (ptr != NULL) {
        GameAllocEntry* entry = &((GameAllocEntry*)ptr)[-1];

        entry->prev->next = entry->next;
        entry->next->prev = entry->prev;
        this->head = this->base.prev;
        free(entry);
    }
}

void gamealloc_cleanup(GameAlloc* this) {
    GameAllocEntry* iter = this->base.next;

    while (&this->base != iter) {
        GameAllocEntry* cur = iter;

        iter = iter->next;
        free(cur);
    }

    this->head = &this->base;
    this->base.next = &this->base;
    this->base.prev = &this->base;
}

void gamealloc_init(GameAlloc* this) {
    this->head = &this->base;
    this->base.next = &this->base;
    this->base.prev = &this->base;
}

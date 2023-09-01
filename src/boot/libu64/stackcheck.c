#include "libc/stdbool.h"
#include "libc/stdint.h"
#include "libu64/stackcheck.h"

StackEntry* sStackInfoListStart = NULL;
StackEntry* sStackInfoListEnd = NULL;

void StackCheck_Init(StackEntry* entry, void* stackBottom, void* stackTop, u32 initValue, s32 minSpace,
                     const char* name) {
    StackEntry* iter;
    u32* addr;

    if (entry == NULL) {
        sStackInfoListStart = NULL;
    } else {
        entry->head = stackBottom;
        entry->tail = stackTop;
        entry->initValue = initValue;
        entry->minSpace = minSpace;
        entry->name = name;

        iter = sStackInfoListStart;
        while (iter) {
            if (iter == entry) {
                return;
            }
            iter = iter->next;
        }

        entry->prev = sStackInfoListEnd;
        entry->next = NULL;

        if (sStackInfoListEnd != NULL) {
            sStackInfoListEnd->next = entry;
        }

        sStackInfoListEnd = entry;
        if (sStackInfoListStart == NULL) {
            sStackInfoListStart = entry;
        }

        if (entry->minSpace != -1) {
            addr = entry->head;
            while (addr < (u32*)entry->tail) {
                *addr++ = entry->initValue;
            }
        }
    }
}

void StackCheck_Cleanup(StackEntry* entry) {
    s32 err = false;

    if (entry->prev == NULL) {
        if (entry == sStackInfoListStart) {
            sStackInfoListStart = entry->next;
        } else {
            err = true;
        }
    } else {
        entry->prev->next = entry->next;
    }

    if (entry->next == NULL) {
        if (entry == sStackInfoListEnd) {
            sStackInfoListEnd = entry->prev;
        } else {
            err = true;
        }
    }

    if (err) {
        // Stubbed debug print
    }
}

s32 StackCheck_GetState(StackEntry* entry) {
    size_t free;
    u32* iter;
    s32 ret;

    for (iter = entry->head; iter < (u32*)entry->tail; iter++) {
        if (*iter != entry->initValue) {
            break;
        }
    }

    free = (uintptr_t)iter - (uintptr_t)entry->head;
    if (free == 0) {
        ret = STACK_STATUS_OVERFLOW;
    } else if ((free < entry->minSpace) && (entry->minSpace != -1)) {
        ret = STACK_STATUS_WARNING;
    } else {
        ret = STACK_STATUS_OK;
    }

    return ret;
}

s32 StackCheck_CheckAll(void) {
    StackEntry* entry = sStackInfoListStart;
    s32 ret = 0;

    while (entry != NULL) {
        if (StackCheck_GetState(entry) != STACK_STATUS_OK) {
            ret = 1;
        }
        entry = entry->next;
    }

    return ret;
}

s32 StackCheck_Check(StackEntry* entry) {
    if (entry == NULL) {
        return StackCheck_CheckAll();
    } else {
        return StackCheck_GetState(entry);
    }
}

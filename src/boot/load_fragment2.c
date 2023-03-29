/**
 * @file loadfragment2.c
 *
 * Functions used to process and relocate overlays.
 *
 */
#include "global.h"
#include "dma.h"
#include "load.h"

s32 gOverlayLogSeverity = 0;

void DoRelocation(void *allocatedRamAddress, OverlayRelocationSection *ovlRelocs, void *vramStart);

s32 Overlay_Load(void *vromStart, void *vromEnd, void *ovlStart, void *ovlEnd, void *vramStart, void *vramEnd,
                 void *allocatedRamAddress, OverlayRelocationSection *ovlRelocs) {
    OverlayRelocationSection *ovl = ovlRelocs;
    s32 vromSize = (uintptr_t)vromEnd - (uintptr_t)vromStart;
    s32 ovlSize = (uintptr_t)ovlEnd - (uintptr_t)ovlStart;
    s32 vramSize = (uintptr_t)vramEnd - (uintptr_t)vramStart;
    void *end = (void *)((uintptr_t)allocatedRamAddress + vromSize);

    DmaMgr_RequestSync(allocatedRamAddress, vromStart, vromSize);
    DmaMgr_RequestSync(ovl, ovlStart, ovlSize);
    DoRelocation(allocatedRamAddress, ovl, vramStart);

    if (ovl->bssSize != 0) {
        bzero(end, ovl->bssSize);
    }

    osWritebackDCache(allocatedRamAddress, vramSize);
    osInvalICache(allocatedRamAddress, vramSize);
    return vramSize;
}

#define MIPS_REG_RS(insn) (((insn) >> 0x15) & 0x1F)

// Extract MIPS register rt from an instruction word
#define MIPS_REG_RT(insn) (((insn) >> 0x10) & 0x1F)

// Extract MIPS jump target from an instruction word
#define MIPS_JUMP_TARGET(insn) (((insn)&0x03FFFFFF) << 2)

void DoRelocation(void *allocatedRamAddress, OverlayRelocationSection *ovlRelocs, void *vramStart) {
    uintptr_t sections[RELOC_SECTION_MAX];
    u32 *relocDataP;
    u32 reloc;
    u32 relocData;
    u32 isLoNeg;
    uintptr_t allocu32 = (uintptr_t)allocatedRamAddress;
    u32 i;
    u32 *regValP;
    //! MIPS ELF relocation does not generally require tracking register values, so at first glance it appears this
    //! register tracking was an unnecessary complication. However there is a bug in the IDO compiler that can cause
    //! relocations to be emitted in the wrong order under rare circumstances when the compiler attempts to reuse a
    //! previous HI16 relocation for a different LO16 relocation as an optimization. This register tracking is likely
    //! a workaround to prevent improper matching of unrelated HI16 and LO16 relocations that would otherwise arise
    //! due to the incorrect ordering.
    u32 *luiRefs[32];
    u32 luiVals[32];
    u32 *luiInstRef;
    UNUSED u32 dbg;
    size_t relocOffset = 0;
    u32 relocatedValue = 0;
    UNUSED uintptr_t unrelocatedAddress = 0;
    uintptr_t relocatedAddress = 0;
    UNUSED s32 pad;

    if (gOverlayLogSeverity >= 3) {}

    sections[RELOC_SECTION_NULL] = 0;
    sections[RELOC_SECTION_TEXT] = allocu32;
    sections[RELOC_SECTION_DATA] = ovlRelocs->textSize + allocu32;
    sections[RELOC_SECTION_RODATA] = ovlRelocs->dataSize + sections[RELOC_SECTION_DATA];

    for (i = 0; i < ovlRelocs->nRelocations; i++) {
        reloc = ovlRelocs->relocations[i];
        // This will always resolve to a 32-bit aligned address as each section
        // containing code or pointers must be aligned to at least 4 bytes and the
        // MIPS ABI defines the offset of both 16-bit and 32-bit relocations to be
        // the start of the 32-bit word containing the target.
        relocDataP = (u32 *)(sections[RELOC_SECTION(reloc)] + RELOC_OFFSET(reloc));
        relocData = *relocDataP;

        switch (RELOC_TYPE_MASK(reloc)) {
            case R_MIPS_32 << RELOC_TYPE_SHIFT:
                // Handles 32-bit address relocation, used for things such as jump tables and pointers in data.
                // Just relocate the full address.

                // Check address is valid for relocation
                if ((*relocDataP & 0x0F000000) == 0) {
                    relocOffset = *relocDataP - (uintptr_t)vramStart;
                    relocatedValue = relocOffset + allocu32;
                    unrelocatedAddress = relocData;
                    relocatedAddress = relocatedValue;
                    *relocDataP = relocatedAddress;
                }
                break;

            case R_MIPS_26 << RELOC_TYPE_SHIFT:
                // Handles 26-bit address relocation, used for jumps and jals.
                // Extract the address from the target field of the J-type MIPS instruction.
                // Relocate the address and update the instruction.
                if (1) {
                    relocOffset = PHYS_TO_K0(MIPS_JUMP_TARGET(*relocDataP)) - (uintptr_t)vramStart;
                    unrelocatedAddress = PHYS_TO_K0(MIPS_JUMP_TARGET(*relocDataP));
                    relocatedValue = (*relocDataP & 0xFC000000) | (((allocu32 + relocOffset) & 0x0FFFFFFF) >> 2);
                    relocatedAddress = PHYS_TO_K0(MIPS_JUMP_TARGET(relocatedValue));
                    *relocDataP = relocatedValue;
                }
                break;

            case R_MIPS_HI16 << RELOC_TYPE_SHIFT:
                // Handles relocation for a hi/lo pair, part 1.
                // Store the reference to the LUI instruction (hi) using the `rt` register of the instruction.
                // This will be updated later in the `R_MIPS_LO16` section.

                luiRefs[MIPS_REG_RT(*relocDataP)] = relocDataP;
                luiVals[MIPS_REG_RT(*relocDataP)] = *relocDataP;
                break;

            case R_MIPS_LO16 << RELOC_TYPE_SHIFT:
                // Handles relocation for a hi/lo pair, part 2.
                // Grab the stored LUI (hi) from the `R_MIPS_HI16` section using the `rs` register of the instruction.
                // The full address is calculated, relocated, and then used to update both the LUI and lo instructions.
                // If the lo part is negative, add 1 to the LUI value.
                // Note: The lo instruction is assumed to have a signed immediate.

                luiInstRef = luiRefs[MIPS_REG_RS(*relocDataP)];
                regValP = &luiVals[MIPS_REG_RS(*relocDataP)];

                // Check address is valid for relocation
                if ((((*regValP << 0x10) + (s16)*relocDataP) & 0x0F000000) == 0) {
                    relocOffset = ((*regValP << 0x10) + (s16)*relocDataP) - (uintptr_t)vramStart;
                    isLoNeg = ((relocOffset + allocu32) & 0x8000) ? 1 : 0; // adjust for signed immediate
                    unrelocatedAddress = (*luiInstRef << 0x10) + (s16)relocData;
                    *luiInstRef =
                        (*luiInstRef & 0xFFFF0000) | ((((relocOffset + allocu32) >> 0x10) & 0xFFFF) + isLoNeg);
                    relocatedValue = (*relocDataP & 0xFFFF0000) | ((relocOffset + allocu32) & 0xFFFF);

                    relocatedAddress = (*luiInstRef << 0x10) + (s16)relocatedValue;
                    *relocDataP = relocatedValue;
                }
                break;
        }

        dbg = 16;
        switch (RELOC_TYPE_MASK(reloc)) {
            case R_MIPS_32 << RELOC_TYPE_SHIFT:
                dbg += 6;
                FALLTHROUGH;
            case R_MIPS_26 << RELOC_TYPE_SHIFT:
                dbg += 10;
                FALLTHROUGH;
            case R_MIPS_LO16 << RELOC_TYPE_SHIFT:
                if (gOverlayLogSeverity >= 3) {}
                // Adding a break prevents matching
        }
    }
}

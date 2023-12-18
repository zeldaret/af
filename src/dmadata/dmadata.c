#include "segment_symbols.h"
#include "m_std_dma.h"

// Linker symbol declarations (used in the table below)
#define DEFINE_DMA_ENTRY(name, _nameString) DECLARE_ROM_SEGMENT(name);

#include "tables/dmadata_table.h"

#undef DEFINE_DMA_ENTRY

// dmadata Table definition
#define DEFINE_DMA_ENTRY(name, _1) { SEGMENT_ROM_START(name), SEGMENT_ROM_END(name), SEGMENT_ROM_START(name), 0 },

DmaEntry dma_rom_ad[] = {
#include "tables/dmadata_table.h"
    { 0 },
};

#undef DEFINE_DMA_ENTRY

u8 sDmaDataPadding[0xF0] = { 0 };

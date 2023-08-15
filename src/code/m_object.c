#include "m_object.h"
#include "segment_symbols.h"

// Segment declarations (also used in the table below)
#define DEFINE_OBJECT(name, _enumValue) DECLARE_ROM_SEGMENT(name);
#define DEFINE_OBJECT_UNSET(_enumValue)

#include "tables/object_table.h"

#undef DEFINE_OBJECT
#undef DEFINE_OBJECT_UNSET

// Object Table definition
#define DEFINE_OBJECT(name, _enumValue) { SEGMENT_ROM_START(name), SEGMENT_ROM_END(name) },
#define DEFINE_OBJECT_UNSET(_enumValue) { 0, 0 },

ObjectOverlay gObjectTable[OBJECT_ID_MAX] = {
#include "tables/object_table.h"
};

#undef DEFINE_OBJECT
#undef DEFINE_OBJECT_UNSET

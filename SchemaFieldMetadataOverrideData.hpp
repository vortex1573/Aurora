#pragma once

#include <cstdint>

#include "FieldType.hpp"

class ISaveRestoreOps;

struct SchemaFieldMetadataOverrideData {
    FieldType m_field_type; // 0x0000
    char pad_0001[7]; // 0x0001
    const char* m_field_name; // 0x0008
    std::uint32_t m_single_inheritance_offset; // 0x0010
    std::int32_t m_field_count; // 0x0014 // @note: @og: if its array or smth like this it will point to count of array
    std::int32_t m_i_unk_1; // 0x0018
    char pad_001C[12]; // 0x001C
    ISaveRestoreOps* m_def_save_restore_ops; // 0x0028
    char pad_0030[16]; // 0x0030
    std::uint32_t m_align; // 0x0040
    char pad_0044[36]; // 0x0044
}; // Size: 0x0068
#pragma once

#include <cstdint>

#include "CSchemaSystemTypeScope.hpp"
#include "SchemaMetadataEntryData.hpp"
#include "SchemaEnumeratorInfoData.hpp"

class CSchemaEnumInfoData {
public:
    CSchemaEnumInfoData* m_self; // 0x0000
    const char* m_name; // 0x0008
    const char* m_module; // 0x0010
    std::int8_t m_align; // 0x0018
    char pad_0x0019[0x3]; // 0x0019
    std::int16_t m_size; // 0x001C
    std::int16_t m_static_metadata_size; // 0x001E
    SchemaEnumeratorInfoData* m_enum_info;
    SchemaMetadataEntryData* m_static_metadata;
    CSchemaSystemTypeScope* m_type_scope; // 0x0030
    char pad_0x0038[0x8]; // 0x0038
    std::int32_t m_i_unk1; // 0x0040
};
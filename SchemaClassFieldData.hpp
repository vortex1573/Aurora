#pragma once

#include <cstdint>

#include "CSchemaType.hpp"
#include "SchemaMetadataEntryData.hpp"

struct SchemaClassFieldData {
    const char* m_name; // 0x0000
    CSchemaType* m_type; // 0x0008
    std::int32_t m_single_inheritance_offset; // 0x0010
    std::int32_t m_metadata_size; // 0x0014
    SchemaMetadataEntryData* m_metadata; // 0x0018
};
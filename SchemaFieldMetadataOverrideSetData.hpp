#pragma once

#include <cstdint>

#include "SchemaFieldMetadataOverrideData.hpp"

struct SchemaFieldMetadataOverrideSetData {
    SchemaFieldMetadataOverrideData* m_metadata_override_data; // 0x0008
    std::int32_t m_size; // 0x0008
};
#pragma once

#include <cstdint>

#include "SchemaMetadataEntryData.hpp"

struct SchemaEnumeratorInfoData {
    const char* m_name;

    union {
        unsigned char m_value_char;
        unsigned short m_value_short;
        unsigned int m_value_int;
        unsigned long long m_value;
    };

    std::int32_t m_metadata_size;
    SchemaMetadataEntryData* m_metadata;
};
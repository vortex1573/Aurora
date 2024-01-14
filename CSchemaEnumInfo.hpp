#pragma once

#include <vector>

#include "CSchemaEnumInfoData.hpp"
#include "SchemaEnumeratorInfoData.hpp"

class CSchemaEnumInfo : public CSchemaEnumInfoData {
public:
    std::vector<SchemaEnumeratorInfoData> GetEnumeratorValues() {
        return { m_enum_info, m_enum_info + m_size };
    }

    std::vector<SchemaMetadataEntryData> GetStaticMetadata() {
        return { m_static_metadata, m_static_metadata + m_static_metadata_size };
    }
};
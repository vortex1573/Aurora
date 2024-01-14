#pragma once

#include <stdexcept>

#include "CSchemaType.hpp"
#include "SchemaClassFlags.hpp"
#include "SchemaClassFieldData.hpp"
#include "SchemaStaticFieldData.hpp"
#include "CSchemaSystemTypeScope.hpp"
#include "SchemaMetadataEntryData.hpp"
#include "SchemaBaseClassInfoData.hpp"
#include "SchemaFieldMetadataOverrideSetData.hpp"

struct SchemaClassInfoData {
public:
    enum class SchemaClassInfoFunctionIndex : std::int32_t {
        kRegisterClassSchema = 0,
        kUnknown = 1, // @note: @og: Can't find fn with such index
        kCopyInstance = 2,
        kCreateInstance = 3,
        kDestroyInstance = 4,
        kCreateInstanceWithMemory = 5,
        kDestroyInstanceWithMemory = 6,
        kSchemaDynamicBinding = 7
    };

public:
    SchemaClassInfoData* m_self; // 0x0000
    const char* m_name; // 0x0008
    const char* m_module; // 0x0010
    int m_size; // 0x0018
    std::int16_t m_fields_size; // 0x001C
    std::int16_t m_static_fields_size; // 0x001E
    std::int16_t m_static_metadata_size; // 0x0020
    std::uint8_t m_align_of; // 0x0022
    std::uint8_t m_has_base_class; // 0x0023
    std::int16_t m_total_class_size; // 0x0024 // @note: @og: if there no derived or base class then it will be 1 otherwise derived class size + 1.
    std::int16_t m_derived_class_size; // 0x0026
    SchemaClassFieldData* m_fields; // 0x0028
    SchemaStaticFieldData* m_static_fields; // 0x0030
    SchemaBaseClassInfoData* m_base_classes; // 0x0038
    SchemaFieldMetadataOverrideSetData* m_field_metadata_overrides; // 0x0040
    SchemaMetadataEntryData* m_static_metadata; // 0x0048
    CSchemaSystemTypeScope* m_type_scope; // 0x0050
    CSchemaType* m_shema_type; // 0x0058
    SchemaClassFlags m_class_flags : 8; // 0x0060
    std::uint32_t m_sequence; // 0x0064 // @note: @og: idk
    void* m_fn; // 0x0068
};
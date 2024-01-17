#pragma once

#include <vector>
#include <optional>
#include <string_view>

#include "SchemaClassFlags.hpp"
#include "SchemaClassInfoData.hpp"
#include "SchemaClassFieldData.hpp"
#include "SchemaStaticFieldData.hpp"
#include "SchemaMetadataEntryData.hpp"
#include "SchemaFieldMetadataOverrideData.hpp"

class CSchemaClassInfo : public SchemaClassInfoData {
public:
    [[nodiscard]] std::string_view GetName() {
        if (m_name)
            return { m_name };
        return {};
    }

    [[nodiscard]] std::string_view GetModule() {
        if (m_module)
            return { m_module };
        return {};
    }

    std::optional<CSchemaClassInfo*> GetBaseClass() const {
        if (m_has_base_class && m_base_classes)
            return m_base_classes->m_prev_by_class;
        return std::nullopt;
    }

    std::vector<SchemaClassFieldData> GetFields() {
        return { m_fields, m_fields + m_fields_size };
    }

    std::vector<SchemaStaticFieldData> GetStaticFields() {
        return { m_static_fields, m_static_fields + m_static_fields_size };
    }

    std::vector<SchemaMetadataEntryData> GetStaticMetadata() {
        return { m_static_metadata, m_static_metadata + m_static_metadata_size };
    }

    std::vector<SchemaFieldMetadataOverrideData> GetStaticFieldMetadataOverrides() const {
        if (!m_field_metadata_overrides)
            return {};

        return { m_field_metadata_overrides->m_metadata_override_data,
                m_field_metadata_overrides->m_metadata_override_data + m_field_metadata_overrides->m_size };
    }

    [[nodiscard]] std::string_view GetPrevClassName() const {
        if (!m_base_classes || !m_base_classes->m_prev_by_class)
            return {};
        return m_base_classes->m_prev_by_class->GetName();
    }

    [[nodiscard]] bool HasVirtualTable() const {
        return (m_class_flags & SCHEMA_CF1_HAS_VIRTUAL_MEMBERS) != 0;
    }

    [[nodiscard]] bool RecursiveHasVirtualTable() const {
        return HasVirtualTable() ? true : (m_base_classes && m_base_classes->m_prev_by_class ? m_base_classes->m_prev_by_class->HasVirtualTable() : false);
    }

    [[nodiscard]] bool IsInherits(const std::string_view from) const {
        if (!m_has_base_class || !m_base_classes || !m_base_classes->m_prev_by_class)
            return false;
        if (m_base_classes->m_prev_by_class->GetName() == from)
            return true;
        return false;
    }

    [[nodiscard]] bool IsRecursiveInherits(const std::string_view from) const {
        return IsInherits(from) ? true :
            (m_base_classes && m_base_classes->m_prev_by_class ? m_base_classes->m_prev_by_class->IsRecursiveInherits(from) : false);
    }

    [[nodiscard]] int GetSize() const {
        return m_size;
    }

    [[nodiscard]] std::uint8_t GetAligment() const {
        return m_align_of == std::numeric_limits<std::uint8_t>::max() ? 8 : m_align_of;
    }

    // @note: @og: Copy instance from original to new created with all data from original, returns new_instance
    void* CopyInstance(void* instance, void* new_instance) const {
        using Fn = void* (*)(SchemaClassInfoFunctionIndex, void*, void*);
        return reinterpret_cast<Fn>(m_fn)(SchemaClassInfoFunctionIndex::kCreateInstance, instance, new_instance);
    }

    // @note: @og: Creates default instance with engine allocated memory (e.g. if SchemaClassInfoData_t is C_BaseEntity, then Instance will be C_BaseEntity)
    void* CreateInstance() const {
        using Fn = void* (*)(SchemaClassInfoFunctionIndex);
        return reinterpret_cast<Fn>(m_fn)(SchemaClassInfoFunctionIndex::kCreateInstance);
    }

    // @note: @og: Creates default instance with your own allocated memory (e.g. if SchemaClassInfoData_t is C_BaseEntity, then Instance will be C_BaseEntity)
    void* CreateInstance(void* memory) const {
        using Fn = void* (*)(SchemaClassInfoFunctionIndex, void*);
        return reinterpret_cast<Fn>(m_fn)(SchemaClassInfoFunctionIndex::kCreateInstanceWithMemory, memory);
    }

    // @note: @og: Destroy instance (e.g.: C_BaseInstance 1st VT fn with 0 flag)
    void* DestroyInstance(void* instance) const {
        using Fn = void* (*)(SchemaClassInfoFunctionIndex, void*);
        return reinterpret_cast<Fn>(m_fn)(SchemaClassInfoFunctionIndex::kDestroyInstanceWithMemory, instance);
    }

    // @note: @og: Destroy instance with de-allocating memory (e.g.: C_BaseInstance 1st VT fn with 1 flag)
    void* DestroyInstanceWithMemory(void* instance) const {
        using Fn = void* (*)(SchemaClassInfoFunctionIndex, void*);
        return reinterpret_cast<Fn>(m_fn)(SchemaClassInfoFunctionIndex::kDestroyInstanceWithMemory, instance);
    }

    CSchemaClassInfo* SchemaClassBinding(void* entity) const {
        using Fn = CSchemaClassInfo * (*)(SchemaClassInfoFunctionIndex, void*);
        return reinterpret_cast<Fn>(m_fn)(SchemaClassInfoFunctionIndex::kSchemaDynamicBinding, entity);
    }
};
#pragma once

#include "Memory.hpp"
#include "CUtlVector.hpp"
#include "CSchemaEnumInfo.hpp"
#include "CSchemaClassInfo.hpp"
#include "CSchemaSystemTypeScope.hpp"

class CSchemaSystem {
private:
    /**
     * \brief (class_info->m_class_flags & 64) != 0;
     */
    using SchemaTypeScope = std::int32_t;

public:
    CSchemaSystemTypeScope* GlobalTypeScope(void) {
        return Memory::CallVirtual<CSchemaSystemTypeScope*>(this, 11u);
    }

    CSchemaSystemTypeScope* FindTypeScopeForModule(const char* module_name) {
        return Memory::CallVirtual<CSchemaSystemTypeScope*>(this, 13u, module_name, nullptr);
    }

    CSchemaSystemTypeScope* GetTypeScopeForBinding(const SchemaTypeScope type, const char* binding) {
        return Memory::CallVirtual<CSchemaSystemTypeScope*>(this, 14u, type, binding);
    }

    const char* GetClassInfoBinaryName(CSchemaClassInfo* class_info) {
        return Memory::CallVirtual<const char*>(this, 22, class_info);
    }

    const char* GetClassProjectName(CSchemaClassInfo* class_info) {
        return Memory::CallVirtual<const char*>(this, 23, class_info);
    }

    const char* GetEnumBinaryName(CSchemaEnumInfo* enum_info) {
        return Memory::CallVirtual<const char*>(this, 24, enum_info);
    }

    const char* GetEnumProjectName(CSchemaEnumInfo* enum_info) {
        return Memory::CallVirtual<const char*>(this, 25, enum_info);
    }

    CSchemaClassInfo* ValidateClasses(CSchemaClassInfo** class_info) {
        return Memory::CallVirtual<CSchemaClassInfo*>(this, CSCHEMASYSTEM_VALIDATECLASSES, class_info);
    }

    bool SchemaSystemIsReady() {
        return Memory::CallVirtual<bool>(this, 26);
    }

    [[nodiscard]] CUtlVector<CSchemaSystemTypeScope*> GetTypeScopes(void) const {
        return m_type_scopes_;
    }

    [[nodiscard]] std::int32_t GetRegistration() const {
        return m_registrations_;
    }

    [[nodiscard]] std::int32_t GetIgnored() const {
        return m_ignored_;
    }

    [[nodiscard]] std::int32_t GetRedundant() const {
        return m_redundant_;
    }

    [[nodiscard]] std::int32_t GetIgnoredBytes() const {
        return m_ignored_bytes_;
    }

private:
    char pad_0x0000[SCHEMASYSTEM_TYPE_SCOPES_OFFSET]; // 0x0000
    CUtlVector<CSchemaSystemTypeScope*> m_type_scopes_ = {}; // SCHEMASYSTEM_TYPE_SCOPES_OFFSET
    char pad_01A0[288] = {}; // 0x01A0
    std::int32_t m_registrations_ = 0; // 0x02C0
    std::int32_t m_ignored_ = 0; // 0x02C4
    std::int32_t m_redundant_ = 0; // 0x02C8
    char pad_02CC[4] = {}; // 0x02CC
    std::int32_t m_ignored_bytes_ = 0; // 0x02D0
};
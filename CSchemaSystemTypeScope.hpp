#pragma once

#include <array>

#include "Memory.hpp"
#include "CUtlTSHash.hpp"
#include "CSchemaType.hpp"
#include "CSchemaEnumInfo.hpp"
#include "CSchemaClassInfo.hpp"
#include "SchemaDefinitions.hpp"

class CSchemaType;
class CSchemaEnumInfo;
class CSchemaClassInfo;

class CSchemaSystemTypeScope {
public:
    CSchemaClassInfo* FindDeclaredClass(const char* class_name) {
        CSchemaClassInfo* class_info;
        Memory::CallVirtual<void>(this, 2, &class_info, class_name);
        return class_info;
    }

    CSchemaEnumInfo* FindDeclaredEnum(const char* name) {
        return Memory::CallVirtual<CSchemaEnumInfo*>(this, 3, name);
    }

    CSchemaType* FindSchemaTypeByName(const char* name, std::uintptr_t* schema) {
        return Memory::CallVirtual<CSchemaType*>(this, 4, name, schema);
    }

    CSchemaType* FindTypeDeclaredClass(const char* name) {
        return Memory::CallVirtual<CSchemaType*>(this, 5, name);
    }

    CSchemaType* FindTypeDeclaredEnum(const char* name) {
        return Memory::CallVirtual<CSchemaType*>(this, 6, name);
    }

    CSchemaClassInfo* FindRawClassBinding(const char* name) {
        return Memory::CallVirtual<CSchemaClassInfo*>(this, 7, name);
    }

    CSchemaEnumInfo* FindRawEnumBinding(const char* name) {
        return Memory::CallVirtual<CSchemaEnumInfo*>(this, 8, name);
    }

    std::string_view GetScopeName() {
        return { m_name_.data() };
    }

    [[nodiscard]] CUtlTSHash<CSchemaClassInfo*> GetClasses() const {
        return m_classes_;
    }

    [[nodiscard]] CUtlTSHash<CSchemaEnumInfo*> GetEnums() const {
        return m_enumes_;
    }
private:
    void* vftable_ = nullptr;
    std::array<char, 256> m_name_ = {};
    char pad_0x0108[SCHEMASYSTEMTYPESCOPE_OFF1] = {}; // 0x0108
    CUtlTSHash<CSchemaClassInfo*> m_classes_; // 0x0588
    char pad_0x0594[SCHEMASYSTEMTYPESCOPE_OFF2] = {}; // 0x05C8
    CUtlTSHash<CSchemaEnumInfo*> m_enumes_; // 0x2DD0
};
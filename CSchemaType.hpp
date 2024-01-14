#pragma once

#include <cstdint>

#include "ETypeCategory.hpp"
#include "SchemaBindings.hpp"
#include "SchemaDefinitions.hpp"
#include "CSchemaSystemTypeScope.hpp"

class CSchemaType {
public:
    bool GetSizes(int* out_size1, uint8_t* unk_probably_not_size) {
        return reinterpret_cast<int(__thiscall*)(void*, int*, uint8_t*)>(vftable_[CSCHEMATYPE_GETSIZES_INDEX])(this, out_size1, unk_probably_not_size);
    }
public:
    bool GetSize(int* out_size) {
        uint8_t smh = 0;
        return GetSizes(out_size, &smh);
    }
public:
    std::uintptr_t* vftable_; // 0x0000
    const char* m_name_; // 0x0008

    CSchemaSystemTypeScope* m_type_scope_; // 0x0010
    std::uint8_t type_category; // ETypeCategory 0x0018
    std::uint8_t atomic_category; // EAtomicCategory 0x0019

    // find out to what class pointer points.
    CSchemaType* GetRefClass() const {
        if (type_category != Schema_Ptr)
            return nullptr;

        auto ptr = m_schema_type_;
        while (ptr && ptr->type_category == ETypeCategory::Schema_Ptr)
            ptr = ptr->m_schema_type_;

        return ptr;
    }

    struct array_t {
        std::uint32_t array_size;
        std::uint32_t unknown;
        CSchemaType* element_type_;
    };

    struct atomic_t { // same goes for CollectionOfT
        std::uint64_t gap[2];
        CSchemaType* template_typename;
    };

    struct atomic_tt {
        std::uint64_t gap[2];
        CSchemaType* templates[2];
    };

    struct atomic_i {
        std::uint64_t gap[2];
        std::uint64_t integer;
    };

    // this union depends on CSchema implementation, all members above
    // is from base class ( CSchemaType )
    union // 0x020
    {
        CSchemaType* m_schema_type_;
        CSchemaClassInfo* m_class_info;
        CSchemaEnumBinding* m_enum_binding_;
        array_t m_array_;
        atomic_t m_atomic_t_;
        atomic_tt m_atomic_tt_;
        atomic_i m_atomic_i_;
    };
};
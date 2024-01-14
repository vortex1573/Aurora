#pragma once

#include "CSchemaType.hpp"

struct SchemaStaticFieldData {
    const char* name; // 0x0000
    CSchemaType* m_type; // 0x0008
    void* m_instance; // 0x0010
    char pad_0x0018[0x10]; // 0x0018
};
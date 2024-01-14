#pragma once

#include <array>
#include <cstdint>

#include "SchemaVarName.hpp"

struct SchemaNetworkValue {
    union {
        const char* m_p_sz_value;
        int m_n_value;
        float m_f_value;
        std::uintptr_t m_p_value;
        SchemaVarName m_var_value;
        std::array<char, 32> m_sz_value;
    };
};
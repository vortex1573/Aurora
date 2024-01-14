#pragma once

enum ETypeCategory {
    Schema_Builtin = 0,
    Schema_Ptr = 1,
    Schema_Bitfield = 2,
    Schema_FixedArray = 3,
    Schema_Atomic = 4,
    Schema_DeclaredClass = 5,
    Schema_DeclaredEnum = 6,
    Schema_None = 7
};
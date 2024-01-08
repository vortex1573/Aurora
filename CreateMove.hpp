#pragma once

#include "Memory.hpp"
#include "Interfaces.hpp"
#include "CHookObject.hpp"

namespace CreateMove {
	void Hook();
	bool __fastcall Detour(void* input, unsigned int nSlot, int64_t unk1, int8_t unk2);

	inline CHookObject<decltype(&Detour)>* hookObject = {};
}
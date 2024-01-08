#include "CreateMove.hpp"

void CreateMove::Hook() {
	hookObject->Create("CCSGOInput", "CreateMove", Memory::GetVirtual<void*>(nullptr, 14U), &Detour);
}

bool __fastcall CreateMove::Detour(void* input, unsigned int nSlot, int64_t unk1, int8_t unk2) {
	const auto original = hookObject->GetOriginal();
	bool originalResult = original(input, nSlot, unk1, unk2);

	if (!Interfaces::Engine->IsConnected() || !Interfaces::Engine->IsInGame())
		return originalResult;

	// Hook code here

	return originalResult;
}
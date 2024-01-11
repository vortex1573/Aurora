#include "Memory.hpp"

const HMODULE Memory::GetBaseModuleHandle(const std::string& moduleName)
{
	const HMODULE moduleHandle = GetModuleHandleA(moduleName.c_str());

	if (!moduleHandle)
		Utility::Error("Failed to get module handle for module '" + moduleName + "'.");

	return moduleHandle;
}

template <typename T = uintptr_t>
T* Memory::GetAbsoluteAddress(T* address, int preOffset, int postOffset)
{
	address += preOffset;
	address += sizeof(int32_t) + *reinterpret_cast<int32_t*>(address);
	address += postOffset;
	return address;
}

uint8_t* Memory::ResolveRelativeAddress(uint8_t* address, uint32_t rvaOffset, uint32_t ripOffset)
{
	uint32_t rvaAddress = *reinterpret_cast<uint32_t*>(address + rvaOffset);
	uint64_t ripAddress = reinterpret_cast<uint64_t>(address) + ripOffset;

	return reinterpret_cast<uint8_t*>(rvaAddress + ripAddress);
}
#include "Memory.hpp"

const HMODULE Memory::GetBaseModuleHandle(const std::string& moduleName)
{
	const HMODULE moduleHandle = GetModuleHandleA(moduleName.c_str());

	if (!moduleHandle) {
		Logger::Error("Failed to get module handle for module '" + moduleName + "'.");
		throw std::runtime_error("Failed to get module handle for module '" + moduleName + "'.");
	}

	return moduleHandle;
}

uintptr_t* Memory::GetAbsoluteAddress(uintptr_t* address, int preOffset, int postOffset)
{
	address += preOffset;
	address += sizeof(int32_t) + *reinterpret_cast<int32_t*>(address);
	address += postOffset;
	return address;
}

uintptr_t* Memory::ResolveRelativeAddress(uintptr_t* address, uint32_t rvaOffset, uint32_t ripOffset)
{
	uintptr_t rvaAddress = *reinterpret_cast<uint32_t*>(address + rvaOffset);
	uintptr_t ripAddress = reinterpret_cast<uint64_t>(address) + ripOffset;

	return reinterpret_cast<uintptr_t*>(rvaAddress + ripAddress);
}
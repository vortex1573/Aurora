#pragma once

#include <Windows.h>
#include <stdexcept>

#include "Utility.hpp"

// https://github.com/maecry/asphyxia-cs2/blob/master/cstrike/utilities/memory.h
// https://www.unknowncheats.me/forum/c-and-c-/277501-calling-virtual-functions-easy.html
namespace Memory {
	const HMODULE GetBaseModuleHandle(const std::string& moduleName);

	template <typename T>
	T* GetAbsoluteAddress(T* address, int preOffset, int postOffset);
	uint8_t* ResolveRelativeAddress(uint8_t* address, uint32_t rvaOffset, uint32_t ripOffset);

	template <typename T>
	__forceinline T GetVirtual(void* instance, size_t index)
	{
		return (*reinterpret_cast<T**>(instance))[index];
	}

	template <typename ReturnType = void*, typename... Args>
	__forceinline ReturnType CallVirtual(void* instance, size_t index, Args... args)
	{
		using fn = ReturnType(__thiscall*)(void*, decltype(args)...);
		return GetVirtual<fn>(instance, index)(instance, args...);
	}
}
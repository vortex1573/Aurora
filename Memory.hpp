#pragma once

#include <Windows.h>
#include <stdexcept>

#include "Logger.hpp"

// https://github.com/maecry/asphyxia-cs2/blob/master/cstrike/utilities/memory.h
// https://www.unknowncheats.me/forum/c-and-c-/277501-calling-virtual-functions-easy.html
namespace Memory {
	const HMODULE GetBaseModuleHandle(const std::string& moduleName);

	uintptr_t* GetAbsoluteAddress(uintptr_t* address, int preOffset, int postOffset);
	uintptr_t* ResolveRelativeAddress(uintptr_t* address, uint32_t rvaOffset, uint32_t ripOffset);

	template <typename T>
	__forceinline T GetVirtual(void* instance, std::size_t index)
	{
		return (*reinterpret_cast<T**>(instance))[index];
	}

	template <std::size_t Index, typename ReturnType = void, typename... Args>
	__forceinline ReturnType CallVirtual(void* instance, Args&&... args)
	{
		using fn = ReturnType(__thiscall*)(void*, decltype(args)...);
		return GetVirtual<fn>(instance, Index)(instance, args...);
	}
}
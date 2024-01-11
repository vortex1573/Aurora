#pragma once

#include "MinHook.h"
#include "Logger.hpp"
#include "Utility.hpp"

template <typename T>
class CHookObject {
private:
	std::string& name;
	void* original = nullptr;
public:
	__forceinline void Create(const std::string& interfaceName, const std::string& hookName, void* target, void* detour)
	{
		this->name = std::format("{0}->{1}", interfaceName, hookName);

		Logger::Debug(std::format("Installing detour {0}.", this->name));

		if (MH_CreateHook(target, detour, reinterpret_cast<void**>(&this->original)) != MH_OK) {}
			Utility::Error(std::format("Failed to install detour {0}.", this->name));
	}

	__forceinline const std::string& GetName()
	{
		return this->name;
	}

	__forceinline T GetOriginal()
	{
		return reinterpret_cast<T>(this->original);
	}
};
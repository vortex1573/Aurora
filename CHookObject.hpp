#pragma once

#include "MinHook.h"
#include "Logger.hpp"

template <typename T>
class CHookObject {
private:
	std::string& name;
	void* original = nullptr;
public:
	void Create(const std::string& interfaceName, const std::string& hookName, void* target, void* detour);

	__forceinline const std::string& GetName()
	{
		return this->name;
	}

	__forceinline T GetOriginal()
	{
		return reinterpret_cast<T>(this->original);
	}
};

template<typename T>
inline void CHookObject<T>::Create(const std::string& interfaceName, const std::string& hookName, void* target, void* detour)
{
	this->Name = std::format("{0}->{1}", interfaceName, hookName);

	Logger::Debug(std::format("Installing detour {0}.", this->Name));

	if (MH_CreateHook(target, detour, reinterpret_cast<T*>(&this->original)) != MH_OK) {
		Logger::Error(std::format("Failed to install detour {0}.", this->Name));
		throw std::runtime_error(std::format("Failed to install detour {0}.", this->Name));
	}
}
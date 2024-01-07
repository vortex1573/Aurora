#pragma once

#include <string>
#include <Windows.h>
#include <stdexcept>

#include "Logger.hpp"
#include "Memory.hpp"
#include "FNVHash.hpp"
#include "IEngineClient.hpp"
#include "CInterfaceRegistry.hpp"

// https://www.unknowncheats.me/forum/counter-strike-2-a/616606-interfaces-grabber-cs2.html
// https://github.com/maecry/asphyxia-cs2/blob/master/cstrike/core/interfaces.cpp
namespace Interfaces {
	inline IEngineClient* Engine = nullptr;

	void Initialize();
	CInterfaceRegistry* GetInterfaceRegistry(const std::string& moduleName, uint8_t* createInterface);
	uintptr_t* GetInterface(const std::string& moduleName, const std::string& interfaceName);
}
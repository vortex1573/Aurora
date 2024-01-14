#pragma once

#include <string>
#include <Windows.h>
#include <stdexcept>

#include "Logger.hpp"
#include "Memory.hpp"
#include "FNVHash.hpp"
#include "Utility.hpp"
#include "CCSGOInput.hpp"
#include "CEngineClient.hpp"
#include "CSchemaSystem.hpp"
#include "CInterfaceRegistry.hpp"

// https://www.unknowncheats.me/forum/counter-strike-2-a/616606-interfaces-grabber-cs2.html
// https://github.com/maecry/asphyxia-cs2/blob/master/cstrike/core/interfaces.cpp
namespace Interfaces {
	inline CEngineClient* Engine = nullptr;
	inline CSchemaSystem* SchemaSystem = nullptr;
	inline CCSGOInput* Input = nullptr;

	void Initialize();
	uint8_t* GetCreateInterface(const std::string& moduleName);
	CInterfaceRegistry* GetInterfaceRegistry(const std::string& moduleName);
	uintptr_t* GetInterface(const std::string& moduleName, const std::string& interfaceName);
}
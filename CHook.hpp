#pragma once

#include <string>

#include "MinHook.h"
#include "Logger.hpp"

class CHook {
private:
	void* Original;

public:
	std::string HookName;
	void* Target;

	CHook(const char* moduleName, const char* name) : HookName(std::format("{0}->{1}", moduleName, name)) {}

	void Install(void* target, void* detour);
	void Uninstall();
};
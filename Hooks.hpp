#pragma once

#include "CHook.hpp"
#include "MinHook.h"
#include "Logger.hpp"

namespace Hooks {
	static bool Initialized = false;

	void Initialize();
	void Shutdown();

	void InstallHooks();
}
#pragma once

#include "MinHook.h"
#include "Logger.hpp"
#include "Utility.hpp"

#include "CreateMove.hpp"

namespace Hooks {
	inline bool Initialized = false;

	void Initialize();
	void Shutdown();

	void InstallHooks();
}
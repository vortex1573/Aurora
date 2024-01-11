#pragma once

#include "MinHook.h"
#include "Logger.hpp"
#include "ErrorHandler.hpp"

#include "CreateMove.hpp"

namespace Hooks {
	static bool Initialized = false;

	void Initialize();
	void Shutdown();

	void InstallHooks();
}
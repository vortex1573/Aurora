#pragma once

#include <chrono>

#include "Hooks.hpp"
#include "Logger.hpp"
#include "Interfaces.hpp"

namespace Instance {
	inline bool Unload = false;

	void Initialize(const HMODULE hModule);
	void Shutdown();
}
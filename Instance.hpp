#pragma once

#include <chrono>

#include "Hooks.hpp"
#include "Utility.hpp"
#include "Interfaces.hpp"

namespace Instance {
	inline bool Unload = false;

	void Initialize(const HMODULE hModule);
	void Shutdown();
}
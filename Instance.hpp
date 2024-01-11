#pragma once

#include <chrono>

#include "Hooks.hpp"
#include "Interfaces.hpp"
#include "ErrorHandler.hpp"

namespace Instance {
	inline bool Unload = false;
	inline HMODULE hModule = nullptr;

	void Initialize(const HMODULE hModule);
	void Shutdown();
}
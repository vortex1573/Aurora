#pragma once

#include <chrono>

#include "Hooks.hpp"
#include "Instance.hpp"
#include "Interfaces.hpp"

namespace Instance {
	inline bool Unload = false;
	inline HMODULE hModule = nullptr;

	void Initialize(const HMODULE hModule);
	void Shutdown();

	void Error(const std::string& errorMessage);
}
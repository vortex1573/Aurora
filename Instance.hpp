#pragma once

#include <chrono>

#include "Menu.hpp"
#include "Hooks.hpp"
#include "Utility.hpp"
#include "DirectX.hpp"
#include "Interfaces.hpp"
#include "InputSystem.hpp"

namespace Instance {
	inline bool Unload = false;

	void Initialize(const HMODULE hModule);
	void Shutdown();
}
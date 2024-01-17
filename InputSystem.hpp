#pragma once

#include <vector>
#include <Windows.h>

#include "imgui.h"
#include "Logger.hpp"
#include "Utility.hpp"

namespace InputSystem {
	inline WNDPROC originalWndProc = nullptr;
	
	inline std::vector<WPARAM> keysDown;

	void Initialize();
	void Shutdown();

	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool IsKeyPressed(WPARAM key);
}
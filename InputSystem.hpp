#pragma once

#include <Windows.h>

#include "imgui.h"
#include "Logger.hpp"
#include "Utility.hpp"

namespace InputSystem {
	inline HWND hWnd = nullptr;
	inline WNDPROC originalWndProc = nullptr;

	void Initialize();
	void Shutdown();
	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}
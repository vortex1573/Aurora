#pragma once

#include <d3d11.h>
#include <Windows.h>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

namespace Menu {
	void Initialize();
	void Shutdown();

	void Render();

	void MiscMenu();
	void SkinsMenu();
	void SettingsMenu();
}
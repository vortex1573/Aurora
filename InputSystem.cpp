#include "InputSystem.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void InputSystem::Initialize()
{
	Logger::Info("Initializing input system.");
	originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(Utility::hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
}

void InputSystem::Shutdown()
{
	SetWindowLongPtrW(Utility::hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(originalWndProc));
}

LRESULT WINAPI InputSystem::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		keysDown.push_back(wParam);
		break;
	case WM_KEYUP:
		if (IsKeyPressed(wParam)) {
			size_t idx = 0;

			for (std::vector<WPARAM>::size_type i = 0; i != keysDown.size(); i++)
				if (keysDown[i] == wParam)
					idx = i;

			keysDown.erase(keysDown.begin() + idx);
		}
		break;
	}

	/*if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;*/

	return CallWindowProcW(originalWndProc, hWnd, msg, wParam, lParam);
}

bool InputSystem::IsKeyPressed(WPARAM key)
{
	for (WPARAM& element : keysDown)
		if (element == key)
			return true;

	return false;
}

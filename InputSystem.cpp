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
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	return CallWindowProcW(originalWndProc, hWnd, msg, wParam, lParam);
}
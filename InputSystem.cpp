#include "InputSystem.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void InputSystem::Initialize()
{
	Logger::Info("Initializing InputSystem.");

	HWND hWnd = FindWindowA(NULL, "cs2.exe");

	if (!hWnd)
		Utility::Error("Failed to get window for 'cs2.exe'.");

	InputSystem::hWnd = hWnd;
	originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
}

void InputSystem::Shutdown()
{
	SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(originalWndProc));
}

LRESULT WINAPI InputSystem::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	return CallWindowProcW(originalWndProc, hWnd, msg, wParam, lParam);
}
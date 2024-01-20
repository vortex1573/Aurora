#pragma once

#pragma warning(disable: 4312)

#include <dxgi.h>
#include <d3d11.h>
#include <Windows.h>

#include "imgui.h"
#include "Menu.hpp"
#include "MinHook.h"
#include "Memory.hpp"
#include "Logger.hpp"
#include "Utility.hpp"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

// https://github.com/rdbo/ImGui-DirectX-11-Kiero-Hook/blob/master/ImGui%20DirectX%2011%20Kiero%20Hook/main.cpp
// https://github.com/rdbo/ImGui-DirectX-11-Kiero-Hook/blob/master/ImGui%20DirectX%2011%20Kiero%20Hook/kiero/kiero.cpp
namespace DirectX {
	inline HWND hwnd;
	inline WNDCLASSEX wndClass;

	inline Present present;
	inline ID3D11Device* device;
	inline ID3D11DeviceContext* context;
	inline ID3D11RenderTargetView* renderTargetView;

	inline uint32_t* methodsTable;

	void Initialize();
	void Shutdown();

	void CreateWindowOverlay();
	void DestroyWindowOverlay();
	void CreateDeviceAndSwapChain();
	const DXGI_FORMAT GetCorrectDXGIFormat(DXGI_FORMAT currentFormat);
	bool CreateRenderTargetView(IDXGISwapChain* swapChain);

	inline bool renderTargetViewInitialized = false;
	HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
}
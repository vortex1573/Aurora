#include "DirectX.hpp"

void DirectX::Initialize()
{
	Logger::Info("Initializing DirectX overlay.");

	CreateWindowOverlay();
	CreateDeviceAndSwapChain();

	void* target = reinterpret_cast<void*>(methodsTable[8]);

	Logger::Debug("Installing detour D3D11->Present.");

	if (MH_CreateHook(target, &present, reinterpret_cast<void**>(&hkPresent)) != MH_OK)
		Utility::Error("Failed to install detour D3D11->Present.");

	if (MH_EnableHook(target) != MH_OK)
		Utility::Error("Failed to enable detour D3D11->Present.");
}

void DirectX::Shutdown()
{
	if (renderTargetView != nullptr) {
		renderTargetView->Release();
		renderTargetView = nullptr;
	}

	free(methodsTable);
	methodsTable = nullptr;
}

void DirectX::CreateWindowOverlay()
{
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(NULL);
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = L"";
	windowClass.hIconSm = NULL;

	wndClass = windowClass;
	RegisterClassEx(&windowClass);
	hwnd = CreateWindow(windowClass.lpszClassName, L"", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);
}

void DirectX::DestroyWindowOverlay()
{
	DestroyWindow(hwnd);
	UnregisterClassW(wndClass.lpszClassName, wndClass.hInstance);
}

void DirectX::CreateDeviceAndSwapChain()
{
	void* createDeviceAndSwapChain = Memory::GetProcessAddress(Memory::GetBaseModuleHandle("d3d11.dll"), "D3D11CreateDeviceAndSwapChain");

	if (!createDeviceAndSwapChain)
		DestroyWindowOverlay();

	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0 };

	DXGI_RATIONAL refreshRate;
	refreshRate.Numerator = 60;
	refreshRate.Denominator = 1;

	DXGI_MODE_DESC bufferDesc;
	bufferDesc.Width = 100;
	bufferDesc.Height = 100;
	bufferDesc.RefreshRate = refreshRate;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SAMPLE_DESC sampleDesc;
	sampleDesc.Count = 1;
	sampleDesc.Quality = 0;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc = sampleDesc;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = 1;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ID3D11Device* tempDevice;
	IDXGISwapChain* tempSwapChain;
	ID3D11DeviceContext* tempContext;

	if (((long(__stdcall*)(
		IDXGIAdapter*,
		D3D_DRIVER_TYPE,
		HMODULE,
		UINT,
		const D3D_FEATURE_LEVEL*,
		UINT,
		UINT,
		const DXGI_SWAP_CHAIN_DESC*,
		IDXGISwapChain**,
		ID3D11Device**,
		D3D_FEATURE_LEVEL*,
		ID3D11DeviceContext**))(createDeviceAndSwapChain))(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, 1, D3D11_SDK_VERSION, &swapChainDesc, &tempSwapChain, &tempDevice, &featureLevel, &tempContext) < 0)
		DestroyWindowOverlay();

	methodsTable = reinterpret_cast<uint32_t*>(calloc(205, sizeof(uint32_t)));
	memcpy(methodsTable, *reinterpret_cast<uint32_t**>(tempSwapChain), 18 * sizeof(uint32_t));
	memcpy(methodsTable + 18, *reinterpret_cast<uint32_t**>(tempDevice), 43 * sizeof(uint32_t));
	memcpy(methodsTable + 18 + 43, *reinterpret_cast<uint32_t**>(tempContext), 144 * sizeof(uint32_t));

	tempSwapChain->Release();
	tempSwapChain = nullptr;

	tempDevice->Release();
	tempDevice = nullptr;

	tempContext->Release();
	tempContext = nullptr;

	DestroyWindowOverlay();
}

const DXGI_FORMAT DirectX::GetCorrectDXGIFormat(DXGI_FORMAT currentFormat)
{
	switch (currentFormat)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	}

	return currentFormat;
}

bool DirectX::CreateRenderTargetView(IDXGISwapChain* swapChain)
{
	if (swapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device)) < 0)
		return false;

	device->GetImmediateContext(&context);
	DXGI_SWAP_CHAIN_DESC sd;
	swapChain->GetDesc(&sd);
	hwnd = sd.OutputWindow;
	ID3D11Texture2D* backBuffer;

	if (swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backBuffer)) < 0)
		return false;

	D3D11_RENDER_TARGET_VIEW_DESC desc;
	desc.Format = static_cast<DXGI_FORMAT>(GetCorrectDXGIFormat(sd.BufferDesc.Format));
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	device->CreateRenderTargetView(backBuffer, &desc, &renderTargetView);

	backBuffer->Release();
	backBuffer = nullptr;

	return true;
}

HRESULT __stdcall DirectX::hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!renderTargetViewInitialized) {
		if (CreateRenderTargetView(pSwapChain)) {
			ImGui_ImplWin32_Init(hwnd);
			ImGui_ImplDX11_Init(device, context);
			renderTargetViewInitialized = true;
		}
		else
			return present(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Menu::Render();

	context->OMSetRenderTargets(1, &renderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return present(pSwapChain, SyncInterval, Flags);
}

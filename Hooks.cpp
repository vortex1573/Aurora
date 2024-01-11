#include "Hooks.hpp"

void Hooks::Initialize()
{
	Logger::Info("Initializing hooks.");

	if (Initialized) {
		Logger::Debug("Already initialized hooks.");
		return;
	}

	Logger::Debug("Initializing MinHook.");

	if (MH_Initialize() != MH_OK)
		Instance::Error("Failed to initialize MinHook.");

	InstallHooks();

	Logger::Debug("Enabling hooks.");

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		Instance::Error("Failed to enable all hooks.");

	Initialized = true;
}

void Hooks::Shutdown()
{
	if (!Initialized) {
		Logger::Debug("Hooks have not been initialized.");
		return;
	}

	if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
		Instance::Error("Failed to disable all hooks.");

	if (MH_Uninitialize() != MH_OK)
		Instance::Error("Failed to uninitialize MinHook.");
}

void Hooks::InstallHooks()
{
	Logger::Debug("Installing hooks.");

	CreateMove::Hook();
}
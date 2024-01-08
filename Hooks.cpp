#include "Hooks.hpp"

void Hooks::Initialize()
{
	Logger::Info("Initializing hooks.");

	if (Initialized) {
		Logger::Debug("Already initialized hooks.");
		return;
	}

	Logger::Debug("Initializing MinHook.");

	if (MH_Initialize() != MH_OK) {
		Logger::Error("Failed to initialize MinHook.");
		throw std::runtime_error("Failed to initialize MinHook.");
	}

	InstallHooks();

	Logger::Debug("Enabling hooks.");

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		Logger::Error("Failed to enable all hooks.");
		throw std::runtime_error("Failed to enable all hooks.");
	}

	Initialized = true;
}

void Hooks::Shutdown()
{
	if (!Initialized) {
		Logger::Debug("Hooks have not been initialized.");
		return;
	}

	if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK) {
		Logger::Error("Failed to disable all hooks.");
		throw std::runtime_error("Failed to disable all hooks.");
	}

	if (MH_Uninitialize() != MH_OK) {
		Logger::Error("Failed to uninitialize MinHook.");
		throw std::runtime_error("Failed to uninitialize MinHook.");
	}
}

void Hooks::InstallHooks()
{
	Logger::Debug("Installing hooks.");

	CreateMove::Hook();
}
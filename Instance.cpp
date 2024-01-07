#include "Instance.hpp"

void Instance::Initialize(const HMODULE hModule)
{
	try {
		std::chrono::milliseconds startMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		Logger::Info("Initializing.");

		Hooks::Initialize();
		Interfaces::Initialize();

		std::chrono::milliseconds endMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		Logger::Info(std::format("Initialized in {0}ms.", endMs.count() - startMs.count()));
	}
	catch (const std::runtime_error& err) {
		MessageBoxA(nullptr, err.what(), "Failed to initialize!", MB_OK | MB_ICONERROR);
		Logger::Error(std::format("Failed to initialize: {0}", err.what()));
		FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
	}
}

void Instance::Shutdown()
{
	Hooks::Shutdown();
	Logger::Shutdown();
}
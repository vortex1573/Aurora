#include "Instance.hpp"

void Instance::Initialize(const HMODULE hModule)
{
	Instance::hModule = hModule;

	try {
		std::chrono::milliseconds startMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		Logger::Info("Initializing.");

		Hooks::Initialize();
		Interfaces::Initialize();

		std::chrono::milliseconds endMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		Logger::Info(std::format("Initialized in {0}ms.", endMs.count() - startMs.count()));
	}
	catch (const std::runtime_error& err) {
		Error(std::format("Failed to initialize: {0}", err.what()));
	}
}

void Instance::Shutdown()
{
	Hooks::Shutdown();
	Logger::Shutdown();
}

void Instance::Error(const std::string& errorMessage)
{
	Logger::Error(errorMessage);
	throw std::runtime_error(errorMessage);

	if (MessageBoxA(nullptr, errorMessage.c_str(), "An error has occurred!", MB_OK | MB_ICONERROR | MB_SETFOREGROUND | MB_TOPMOST) == IDOK)
		FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
}
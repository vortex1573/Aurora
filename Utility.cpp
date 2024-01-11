#include "Utility.hpp"

void Utility::Initialize(const HMODULE hModule, const std::string& folderPath, const std::string& extension)
{
	Utility::hModule = hModule;
	Utility::extension = extension;
	Utility::folderPath = folderPath;
}

void Utility::Error(const std::string& errorMessage)
{
	Logger::Error(errorMessage);
	throw std::runtime_error(errorMessage);

	if (MessageBoxA(nullptr, errorMessage.c_str(), "An error has occurred!", MB_OK | MB_ICONERROR | MB_SETFOREGROUND | MB_TOPMOST) == IDOK)
		FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
}
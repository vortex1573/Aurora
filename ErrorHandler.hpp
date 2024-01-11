#pragma once

#include "Logger.hpp"

namespace ErrorHandler {
	inline HMODULE hModule = nullptr;

	inline void Error(const std::string& errorMessage)
	{
		Logger::Error(errorMessage);
		throw std::runtime_error(errorMessage);

		if (MessageBoxA(nullptr, errorMessage.c_str(), "An error has occurred!", MB_OK | MB_ICONERROR | MB_SETFOREGROUND | MB_TOPMOST) == IDOK)
			FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
	}
}
#pragma once

#include <string>
#include <Windows.h>

#include "Logger.hpp"

namespace Utility {
	inline std::string extension;
	inline std::string folderPath;

	inline HWND hWnd = nullptr;
	inline HMODULE hModule = nullptr;

	void Initialize(const HMODULE hModule, const std::string& folderPath, const std::string& extension);
	void Error(const std::string& errorMessage);
}
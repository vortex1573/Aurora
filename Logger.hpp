#pragma once

#include <ctime>
#include <chrono>
#include <string>
#include <format>
#include <iomanip>
#include <iostream>
#include <Windows.h>

#include "Color.hpp"
#include "Defines.hpp"

namespace Logger {
	static std::time_t time_now = std::time(nullptr);
	static FILE* ConsoleStream;
	static bool Initialized;

	enum Types {
		NONE,
		INFO,
		WARN,
		ERR,
		DEBUG
	};

	void Initialize();
	void Shutdown();

	const dye::colorful<std::string> FormatType(Types type);
	const dye::colorful<std::string> GetCheatName();
	const dye::colorful<std::string> GetTimestamp();

	void Log(const std::string& msg);
	void Log(const std::string& title, const std::string& msg);
	void Log(const Types type, const std::string& msg);
	void Log(const Types type, const std::string& title, const std::string& msg);

	void Info(const std::string& msg);
	// void Info(const std::string& title, const std::string& msg);
	void Warn(const std::string& msg);
	// void Warn(const std::string& title, const std::string& msg);
	void Error(const std::string& msg);
	// void Error(const std::string& title, const std::string& msg);
	void Debug(const std::string& msg);
	// void Debug(const std::string& title, const std::string& msg);
}
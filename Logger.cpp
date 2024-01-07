#include "Logger.hpp"

void Logger::Initialize()
{
	if (Initialized) return;

#ifdef LOGGING_ENABLED
	AllocConsole();
	SetConsoleTitleA(CHEAT_NAME);

	freopen_s(&ConsoleStream, "CONOUT$", "w", stdout);
	Initialized = true;
#endif
}

void Logger::Shutdown()
{
	fclose(ConsoleStream);
	FreeConsole();
	PostMessageW(GetConsoleWindow(), WM_CLOSE, NULL, NULL);
}

const dye::colorful<std::string> Logger::FormatType(Types type)
{
	switch (type)
	{
	case Logger::INFO:
		return dye::light_green("[INFO] ");
	case Logger::WARN:
		return dye::yellow("[WARN] ");
	case Logger::ERR:
		return dye::red("[ERROR] ");
	case Logger::DEBUG:
		return dye::purple("[DEBUG] ");
	}

	return dye::grey("[PRINT] ");
}

const dye::colorful<std::string> Logger::GetCheatName()
{
	return dye::light_blue("[" CHEAT_NAME "] ");
}

const dye::colorful<std::string> Logger::GetTimestamp()
{
	struct std::tm t;
	localtime_s(&t, &time_now);
	std::ostringstream stream;
	stream << std::put_time(&t, "%D %T");

	return dye::grey("[" + stream.str() + "]: ");
}

void Logger::Log(const std::string& msg)
{
#ifdef LOGGING_ENABLED
	std::cout << GetTimestamp() + FormatType(Types::NONE) + GetCheatName() + msg << std::endl;
#endif
}

void Logger::Log(const std::string& title, const std::string& msg)
{
#ifdef LOGGING_ENABLED
	std::cout << GetTimestamp() + FormatType(Types::NONE) + GetCheatName() + "[" + title + "]" + msg << std::endl;
#endif
}

void Logger::Log(const Types type, const std::string& msg)
{
#ifdef LOGGING_ENABLED
	std::cout << GetTimestamp() + FormatType(type) + GetCheatName() + msg << std::endl;
#endif
}

void Logger::Log(const Types type, const std::string& title, const std::string& msg)
{
#ifdef LOGGING_ENABLED
	std::cout << GetTimestamp() + FormatType(type) + GetCheatName() + "[" + title + "]" + msg << std::endl;
#endif
}

void Logger::Info(const std::string& msg)
{
#ifdef LOGGING_ENABLED
	std::cout << GetTimestamp() + FormatType(Types::INFO) + GetCheatName() + msg << std::endl;
#endif
}

void Logger::Warn(const std::string& msg)
{
#ifdef LOGGING_ENABLED
	std::cout << GetTimestamp() + FormatType(Types::WARN) + GetCheatName() + msg << std::endl;
#endif
}

void Logger::Error(const std::string& msg)
{
#ifdef LOGGING_ENABLED
	std::cout << GetTimestamp() + FormatType(Types::ERR) + GetCheatName() + msg << std::endl;
#endif
}

void Logger::Debug(const std::string& msg)
{
#if defined(DEBUG_LOGS_ENABLED) || defined(_DEBUG)
	std::cout << GetTimestamp() + FormatType(Types::DEBUG) + GetCheatName() + msg << std::endl;
#endif
}
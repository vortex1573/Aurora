#pragma once

#define CHEAT_NAME "AURORA"
#define FOLDER_PATH "C:\\Documents\\Aurora"
#define FILE_EXTENSION ".json"

#if defined(_DEBUG) || defined(_TESTING)
#define LOGGING_ENABLED
#endif

#ifdef _DEBUG
#define DEBUG_LOGS_ENABLED
#endif
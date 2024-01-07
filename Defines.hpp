#pragma once

#define CHEAT_NAME "AURORA"

#if defined(_DEBUG) || defined(_TESTING)
#define LOGGING_ENABLED
#endif

#ifdef _DEBUG
#define DEBUG_LOGS_ENABLED
#endif
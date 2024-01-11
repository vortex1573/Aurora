#include <thread>
#include <Windows.h>

#include "Logger.hpp"
#include "Utility.hpp"
#include "Defines.hpp"
#include "Instance.hpp"

DWORD WINAPI Initialize(LPVOID data)
{
    const HMODULE hModule = reinterpret_cast<HMODULE>(data);

    while (!Memory::GetBaseModuleHandle("navsystem.dll"))
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

    Logger::Initialize();
    Logger::Info("Initialized logger.");
    Instance::Initialize(hModule);
    Utility::Initialize(hModule, FOLDER_PATH, FILE_EXTENSION);

    while (!Instance::Unload)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(data), EXIT_SUCCESS);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD callReason, LPVOID lpReserved)
{
    if (callReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);

        if (const HANDLE threadHandle = CreateThread(NULL, NULL, Initialize, hModule, NULL, NULL); threadHandle != nullptr)
            CloseHandle(threadHandle);
    }

    if (callReason == DLL_PROCESS_DETACH && !lpReserved)
        Instance::Shutdown();

    return TRUE;
}
#include "pch.h"
#include "user/main.h"
#include <thread>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            utils::attachConsole();
            if (PipeManager::isUsingPipes())
                PipeManager::getInstance().start();

            std::thread(Main::run).detach();
            break;

        case DLL_PROCESS_DETACH:
            if (lpReserved == nullptr)
            {
                Main::shutdown();
                PipeManager::getInstance().stop();
            }
            break;

        default:
            break;
    }

    return TRUE;
}

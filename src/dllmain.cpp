#include "pch.h"
#include "user/main.h"
#include <thread>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD   ul_reason_for_call, LPVOID  lpReserved)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
        return TRUE;

    DisableThreadLibraryCalls(hModule);

    std::thread([]() {
		Main main;
		main.run();
	}).detach();

    return TRUE;

}

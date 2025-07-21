#include "pch.h"
#include "main.h"

#include "cheat/cheat.h"


void Main::run()
{
    Utils::attachConsole();

    LOG_INFO("Starting initialization...");
    Sleep(1000);

    if (!initializeUnity())
        LOG_ERROR("Unable to initialize Unity! Maybe assemblies are not found?");

    // Initialize renderer
    Renderer& renderer = Renderer::getInstance();
    if (renderer.initialize())
    {
        LOG_INFO("Renderer initialized successfully!");
        LOG_INFO("Using backend: %s", renderer.getBackend()->getName());
        LOG_INFO("Press INSERT to toggle GUI visibility");
    }
    else
    {
        LOG_INFO("Failed to initialize renderer!");
    }

    Cheat::init();
}

UnityModuleBackendInfo Main::getUnityBackend()
{
    LOG_INFO("Finding Unity backend...");

    UnityModuleBackendInfo info;
    info.module = nullptr;
    info.mode = UnityResolve::Mode::Mono;

    // Check if Unity is loaded
    auto unityModule = GetModuleHandleA("UnityPlayer.dll");
    if (unityModule == nullptr)
    {
        LOG_ERROR("UnityPlayer.dll not found! Is this a Unity game?");
        return info;
    }

    auto assembly = GetModuleHandleA("GameAssembly.dll");
    if (assembly)
    {
        info.module = assembly;
        info.mode = UnityResolve::Mode::Il2Cpp;
        LOG_INFO("Found Il2Cpp backend!");
        return info;
    }
    LOG_WARNING("GameAssembly.dll not found, trying fallback to Mono...");
    assembly = GetModuleHandleA("mono-2.0-bdwgc.dll"); // Newer versions of Unity I think
    if (assembly)
    {
        info.module = assembly;
        info.mode = UnityResolve::Mode::Mono;
        LOG_INFO("Found Mono backend!");
        return info;
    }
    assembly = GetModuleHandleA("mono.dll");
    if (assembly)
    {
        info.module = assembly;
        info.mode = UnityResolve::Mode::Mono;
        LOG_INFO("Found Mono backend!");
        return info;
    }

    LOG_ERROR("Unable to find Unity backend! Neither GameAssembly.dll nor mono.dll found.");
    return info;
}

bool Main::initializeUnity()
{
    auto backend = getUnityBackend();
    if (backend.module == nullptr)
    {
        LOG_ERROR("Unity backend not found!");
        return false;
    }

    UnityResolve::Init(backend.module, backend.mode);

    return true;
}

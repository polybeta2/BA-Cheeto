#include "pch.h"
#include "main.h"

#include "core/rendering/renderer.h"
#include "cheat/cheat.h"

void Main::run()
{
    utils::attachConsole();

    LOG_INFO("Starting initialization...");
    Sleep(1000);

    if (!initializeUnity())
        LOG_ERROR("Unable to initialize Unity! Maybe assemblies are not found?");

    // Initialize renderer
    if (Renderer& renderer = Renderer::getInstance(); renderer.initialize())
    {
        LOG_INFO("Renderer initialized successfully!");
        LOG_INFO("Press INSERT to toggle GUI visibility");
    }
    else
    {
        LOG_INFO("Failed to initialize renderer!");
    }

    cheat::init();

    auto battleClass = app::getClass("BlueArchive.dll", "Battle");
    auto fAfter = app::findMethodAfter(battleClass, "Resume");
    auto fBetween = app::findMethodBetween(battleClass, "Resume", "Push");
    auto fBefore = app::findMethodBefore(battleClass, "Push");
    LOG_DEBUG("fAfter %p, fBetween %p, fBefore %p",
			  app::getMethodAddress(fAfter), app::getMethodAddress(fBetween), app::getMethodAddress(fBefore));
}

UnityModuleBackendInfo Main::getUnityBackend()
{
    LOG_INFO("Finding Unity backend...");

    UnityModuleBackendInfo info;
    info.module = nullptr;
    info.mode = UnityResolve::Mode::Mono;

    // Check if Unity is loaded
    if (const auto unityModule = GetModuleHandleA("UnityPlayer.dll"); unityModule == nullptr)
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
    auto [module, mode] = getUnityBackend();
    if (module == nullptr)
    {
        LOG_ERROR("Unity backend not found!");
        return false;
    }

    UnityResolve::Init(module, mode);

    return true;
}

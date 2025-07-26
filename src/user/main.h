#pragma once

class Main
{
public:
    static void run();
    static void shutdown();

private:
    struct UnityModuleBackendInfo
    {
        void* module;
        UnityResolve::Mode mode;
    };

    static UnityModuleBackendInfo getUnityBackend();
    static bool initializeUnity();
};

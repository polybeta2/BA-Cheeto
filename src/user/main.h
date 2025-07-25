#pragma once

class Main
{
public:
    static void run();

private:
    struct UnityModuleBackendInfo
    {
        void* module;
        UnityResolve::Mode mode;
    };
    
    static UnityModuleBackendInfo getUnityBackend();
    static bool initializeUnity();
};

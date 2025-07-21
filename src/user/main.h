#pragma once

struct UnityModuleBackendInfo
{
    void* module;
    UnityResolve::Mode mode;
};

class Main
{
public:
    static void run();

private:
    static UnityModuleBackendInfo getUnityBackend();
    static bool initializeUnity();
};

#pragma once

#include <UnityResolve.hpp>

namespace App
{
    inline UnityResolve::Class* getClass(const std::string& module, const std::string& className)
    {
        auto unityModule = UnityResolve::Get(module);
        if (!unityModule)
        {
            LOG_ERROR("Module '%s' not found", module.c_str());
            return nullptr;
        }

        auto unityClass = unityModule->Get(className);
        if (!unityClass)
        {
            LOG_ERROR("Class '%s' not found in module '%s'", className.c_str(), module.c_str());
            return nullptr;
        }

        return unityClass;
    }

    inline UnityResolve::Method* getMethod(const std::string& module,
                                           const std::string& className, const std::string& methodName)
    {
        auto unityClass = getClass(module, className);
        if (!unityClass)
        {
            LOG_ERROR("Failed to get class '%s' from module '%s'", className.c_str(), module.c_str());
            return nullptr;
        }

        auto method = unityClass->Get<UnityResolve::Method>(methodName);
        if (!method)
        {
            LOG_ERROR("Method '%s' not found in class '%s' of module '%s'", methodName.c_str(), className.c_str(),
                      module.c_str());
            return nullptr;
        }

        return method;
    }

    inline UnityResolve::Method* getMethod(UnityResolve::Class* unityClass, const std::string& methodName)
    {
        if (!unityClass)
        {
            LOG_ERROR("Unity class is null");
            return nullptr;
        }

        auto method = unityClass->Get<UnityResolve::Method>(methodName);
        if (!method)
        {
            LOG_ERROR("Method '%s' not found in class '%s'", methodName.c_str(), unityClass->name.c_str());
            return nullptr;
        }

        return method;
    }

    inline void* getMethodAddress(const std::string& module,
                                  const std::string& className, const std::string& methodName)
    {
        auto method = getMethod(module, className, methodName);
        if (!method)
        {
            LOG_ERROR("Failed to get method '%s' from class '%s' in module '%s'", methodName.c_str(), className.c_str(),
                      module.c_str());
            return nullptr;
        }

        return *static_cast<void**>(method->address);
    }

    inline void* getMethodAddress(UnityResolve::Class* unityClass, const std::string& methodName)
    {
        if (!unityClass)
        {
            LOG_ERROR("Unity class is null");
            return nullptr;
        }

        auto method = getMethod(unityClass, methodName);
        if (!method)
        {
            LOG_ERROR("Failed to get method '%s' from class '%s'", methodName.c_str(), unityClass->name.c_str());
            return nullptr;
        }

        return *static_cast<void**>(method->address);
    }

    inline void* getMethodAddress(UnityResolve::Method* method)
    {
        if (!method)
        {
            LOG_ERROR("Unity method is null");
            return nullptr;
        }

        return *static_cast<void**>(method->address);
    }
}

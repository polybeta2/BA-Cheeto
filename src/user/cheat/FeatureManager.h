#pragma once
#include "FeatureBase.h"

namespace cheat
{
    class FeatureManager
    {
    public:
        static FeatureManager& getInstance();

    private:
        FeatureManager() = default;
    };
}

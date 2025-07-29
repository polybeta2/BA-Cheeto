#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class GodMode : public FeatureBase
    {
        DECL_SINGLETON(GodMode)

    public:
        GodMode();
    };
};

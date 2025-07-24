#pragma once
#include "user/cheat/FeatureBase.h"

namespace cheat::features
{
    class GodMode : public FeatureBase
    {
        DECL_SINGLETON(GodMode)
    public:
        GodMode();

        void onEnable() override;
        void onDisable() override;
    };
};

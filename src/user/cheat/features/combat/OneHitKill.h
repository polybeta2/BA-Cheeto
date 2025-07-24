#pragma once
#include "user/cheat/FeatureBase.h"

namespace cheat::features
{
    class OneHitKill : public FeatureBase
    {
        DECL_SINGLETON(OneHitKill)

    public:
        OneHitKill();

        void onEnable() override;
        void onDisable() override;
    };
}

#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class OneHitKill : public FeatureBase
    {
        DECL_SINGLETON(OneHitKill)

    public:
        OneHitKill();
    };
}

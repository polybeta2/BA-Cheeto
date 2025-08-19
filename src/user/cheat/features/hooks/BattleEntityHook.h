#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class BattleEntityHook : public FeatureBase<BattleEntityHook>
    {
    public:
        BattleEntityHook();

    private:
        static int64_t hBattleEntity_AddHitPoint(BattleEntity* _this, int64_t value);
    };
}

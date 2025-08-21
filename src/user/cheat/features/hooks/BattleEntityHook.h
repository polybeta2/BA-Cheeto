#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class BattleEntityHook : public FeatureBase<BattleEntityHook>
    {
    public:
        BattleEntityHook();

    private:
        static int64_t BattleEntity_AddHitPoint_Hook(BattleEntity* _this, int64_t value);
    };
}

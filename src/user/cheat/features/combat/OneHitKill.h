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

    private:
        static int64_t hBattleEntity_AddHitPoint(BattleEntity* _this, int64_t value);
    };
}

#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class SkipBattleSummary : public FeatureBase
    {
        DECL_SINGLETON(SkipBattleSummary)

    public:
        SkipBattleSummary();

    private:
        static void hBattleSceneHandler_Update(BattleSceneHandler* _this);
    };
}

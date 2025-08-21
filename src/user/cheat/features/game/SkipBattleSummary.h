#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class SkipBattleSummary : public FeatureBase<SkipBattleSummary>
    {
        DECL_SINGLETON(SkipBattleSummary)

    public:
        SkipBattleSummary();

    private:
        static void BattleSceneHandler_Update_Hook(BattleSceneHandler* _this);
    };
}

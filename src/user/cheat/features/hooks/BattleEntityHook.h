#pragma once
#include "user/cheat/FeatureBase.h"

namespace cheat::features
{
    class BattleEntityHook : public FeatureBase
    {
    public:
        BattleEntityHook();

    private:
        static int64_t hBattleEntity_AddHitPoint(BattleEntity* _this, int64_t value);

        static bool s_oneHitKillEnabled;
        static bool s_godModeEnabled;

        static void onOneHitKillEnabled();
        static void onOneHitKillDisabled();
        static void onGodModeEnabled();
        static void onGodModeDisabled();
    };
}

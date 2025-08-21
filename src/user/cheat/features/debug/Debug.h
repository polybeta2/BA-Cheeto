#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class Debug : public FeatureBase<Debug>
    {
        DECL_SINGLETON(Debug)

    public:
        Debug();

        void draw() override;

    private:
        bool m_test0;

        static void BattleEntity_ApplyStat_Hook(BattleEntity* _this, StatType_Enum statType);
        static void BattleEntityStatProcessor_Apply_Hook(BattleEntityStatProcessor* _this, StatType_Enum statType);
        static void* Character_ApplyDamage_Hook(Character* _this, BattleEntity* attacker, DamageResult damageResult);
    };
}

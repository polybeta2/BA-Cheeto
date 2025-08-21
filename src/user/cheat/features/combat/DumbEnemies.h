#pragma once
#include "user/cheat/feature_base.h"

namespace cheat::features
{
    class DumbEnemies : public FeatureBase<DumbEnemies>
    {
        DECL_SINGLETON(DumbEnemies)

    public:
        DumbEnemies();

        void draw() override;

    private:
        bool m_dumbPlayer = false; // For testing

        static bool BattleEntity_get_HasMainTarget_Hook(BattleEntity* _this);
        // static bool BattleEntity_CanBeTargeted_Hook(BattleEntity* _this, BattleEntity* attacker, SkillSlot_Enum skillSlot);
    };
}

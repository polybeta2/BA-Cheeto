#pragma once
#include "user/cheat/FeatureBase.h"

namespace cheat::features
{
    class DumbEnemies : public FeatureBase
    {
        DECL_SINGLETON(DumbEnemies)

    public:
        DumbEnemies();

        void draw() override;
        void onEnable() override;
        void onDisable() override;

    private:
        bool m_dumbPlayer = false;

        static bool hBattleEntity_CanBeTargeted(BattleEntity* _this, BattleEntity* attacker, SkillSlot_Enum skillSlot);
    };
}

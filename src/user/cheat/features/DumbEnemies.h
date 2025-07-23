#pragma once
#include "user/cheat/FeatureBase.h"

namespace cheat::features
{
    class DumbEnemies : public FeatureBase
    {
        DECL_SINGLETON(DumbEnemies)
        
    public:
        DumbEnemies();
        
        bool init() override;
        void draw() override;

        void onEnable() override;
        void onDisable() override;

    private:
        static bool hCanBeTargeted(BattleEntity* _this, BattleEntity* attacker, SkillSlot_Enum skillSlot);
    };
}

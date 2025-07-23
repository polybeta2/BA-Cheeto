#include "pch.h"
#include "DumbEnemies.h"

#include "appdata/types.h"

namespace cheat::features
{
    DumbEnemies::DumbEnemies()
        : FeatureBase("Dumb Enemies", "Enemies ignore targeting you",
                      FeatureSection::Combat)
    {
        HookManager::install(BattleEntity::CanBeTargeted(), hBattleEntity_CanBeTargeted);
    }

    void DumbEnemies::onEnable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s enabled", getName().c_str());
    }

    void DumbEnemies::onDisable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s disabled", getName().c_str());
    }

    bool DumbEnemies::hBattleEntity_CanBeTargeted(BattleEntity* _this, BattleEntity* attacker, SkillSlot_Enum skillSlot)
    {
        if (s_instance->isEnabled())
        {
            if (_this->TacticEntityType() == TacticEntityType_Enum::Student) return false;
        }

        return CALL_ORIGINAL(hBattleEntity_CanBeTargeted, _this, attacker, skillSlot);
    }
}

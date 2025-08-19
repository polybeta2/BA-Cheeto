#include "pch.h"
#include "DumbEnemies.h"

#include "appdata/types.h"

namespace cheat::features
{
    static constexpr auto blockedTypes = std::to_array({
        TacticEntityType_Enum::Minion,
        TacticEntityType_Enum::Elite,
        TacticEntityType_Enum::Champion,
        TacticEntityType_Enum::Boss
    });

    DumbEnemies::DumbEnemies()
        : FeatureBase("Dumb Enemies", "Enemies ignore targeting you",
                      FeatureSection::Combat)
    {
        HookManager::install(BattleEntity::get_HasMainTarget(), hBattleEntity_get_HasMainTarget);
        // HookManager::install(BattleEntity::CanBeTargeted(), hBattleEntity_CanBeTargeted);
    }

    void DumbEnemies::draw()
    {
        // ImGui::Checkbox("Dumb Player", &m_dumbPlayer);
    }

    // bool DumbEnemies::hBattleEntity_CanBeTargeted(BattleEntity* _this, BattleEntity* attacker, SkillSlot_Enum skillSlot)
    // {
    //     // if (s_instance->isEnabled())
    //     // {
    //     //     if (_this->TacticEntityType() == TacticEntityType_Enum::Student) return false;
    //     // }
    //
    //     // For testing
    //     // if (s_instance->m_dumbPlayer)
    //     // {
    //     //     if (attacker->TacticEntityType() == TacticEntityType_Enum::Student) return false;
    //     // }
    //
    //     return CALL_ORIGINAL(hBattleEntity_CanBeTargeted, _this, attacker, skillSlot);
    // }

    bool DumbEnemies::hBattleEntity_get_HasMainTarget(BattleEntity* _this)
    {
        if (s_instance->isEnabled() &&
            std::ranges::find(blockedTypes, _this->TacticEntityType()) != blockedTypes.end())
            BattleEntity::ClearTarget()(_this);

        return CALL_ORIGINAL(hBattleEntity_get_HasMainTarget, _this);
    }
}

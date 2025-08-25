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
        BattleEntity::get_HasMainTarget_Hook().set(BattleEntity_get_HasMainTarget_Hook);
        // BattleEntity::CanBeTargeted_Hook().set(BattleEntity_CanBeTargeted_Hook);
    }

    void DumbEnemies::draw()
    {
        // ImGui::Checkbox("Dumb Player", &m_dumbPlayer);
    }

    // bool DumbEnemies::BattleEntity_CanBeTargeted_Hook(BattleEntity* _this, BattleEntity* attacker, SkillSlot_Enum skillSlot)
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
    //     return BattleEntity::CanBeTargeted_Hook().call(_this, attacker, skillSlot);
    // }

    bool DumbEnemies::BattleEntity_get_HasMainTarget_Hook(BattleEntity* _this)
    {
        if (s_instance->isEnabled() &&
            std::ranges::find(blockedTypes, _this->TacticEntityType()) != blockedTypes.end())
            BattleEntity::ClearTarget()(_this);

        return BattleEntity::get_HasMainTarget_Hook().call(_this);
    }
}

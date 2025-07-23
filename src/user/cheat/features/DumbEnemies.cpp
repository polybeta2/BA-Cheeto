#include "pch.h"
#include "DumbEnemies.h"

#include "appdata/types.h"

namespace cheat::features
{
    DumbEnemies::DumbEnemies()
        : FeatureBase("Dumb Enemies", "Enemies ignore targeting you",
                      FeatureSection::Combat)
    {
    }

    void DumbEnemies::draw()
    {
    }

    void DumbEnemies::onEnable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s enabled", getName());
    }

    void DumbEnemies::onDisable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s disabled", getName());
    }

    bool DumbEnemies::hCanBeTargeted(BattleEntity* _this, BattleEntity* attacker, SkillSlot_Enum skillSlot)
    {
        if (s_instance->isEnabled())
        {
            if (_this->TacticEntityType() == TacticEntityType_Enum::Student) return false;
        }

        // LOG_INFO("hCanBeTargeted called for BattleEntity at %p with attacker at %p", _this, attacker);
        // LOG_INFO("TacticalEntityType: %s", magic_enum::enum_name(_this->TacticEntityType()).data());
        // LOG_INFO("HitPoint %d", _this->HitPoint()); // can be used for god mode i think
        // LOG_INFO("HitPointBefore %d", _this->HitPointBefore()); // can be used for god mode i think
        // LOG_INFO("MaxHPCapGauge %d", _this->MaxHPCapGauge());
        // LOG_INFO("SummonedTime %d", _this->SummonedTime());

        return CALL_ORIGINAL(hCanBeTargeted, _this, attacker, skillSlot);
    }

    bool DumbEnemies::init()
    {
        return HookManager::install(BattleEntity::CanBeTargeted(), hCanBeTargeted);
    }
}

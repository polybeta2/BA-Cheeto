#include "pch.h"
#include "OneHitKill.h"

#include "appdata/types.h"

namespace cheat::features
{
    OneHitKill::OneHitKill()
        : FeatureBase("One Hit Kill", "Enemies die in one hit",
                      FeatureSection::Combat)
    {
        HookManager::install(BattleEntity::AddHitPoint(), hBattleEntity_AddHitPoint);
    }

    void OneHitKill::onEnable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s enabled", getName().c_str());
    }

    void OneHitKill::onDisable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s disabled", getName().c_str());
    }

    int64_t OneHitKill::hBattleEntity_AddHitPoint(BattleEntity* _this, int64_t value)
    {
        if (s_instance->isEnabled())
        {
            if (_this->TacticEntityType() == TacticEntityType_Enum::Minion ||
                // _this->TacticEntityType() == TacticEntityType_Enum::Elite ||
                // _this->TacticEntityType() == TacticEntityType_Enum::Champion ||
                _this->TacticEntityType() == TacticEntityType_Enum::Boss ||
                _this->TacticEntityType() == TacticEntityType_Enum::Obstacle ||
                _this->TacticEntityType() == TacticEntityType_Enum::Vehicle)
            {
                _this->HitPoint(1);
                _this->HitPointBefore(1);
            }

            // LOG_INFO("TacticalEntityType: %s", magic_enum::enum_name(_this->TacticEntityType()).data());
            // LOG_INFO("value %d", value);
            // LOG_INFO("HitPoint %d", _this->HitPoint()); // can be used for god mode i think
            // LOG_INFO("HitPointBefore %d", _this->HitPointBefore()); // can be used for god mode i think
            // LOG_INFO("MaxHPCapGauge %d", _this->MaxHPCapGauge());
            // LOG_INFO("ArmorType %s", magic_enum::enum_name(_this->ArmorType()).data());
        }

        return CALL_ORIGINAL(hBattleEntity_AddHitPoint, _this, value);
    }
}

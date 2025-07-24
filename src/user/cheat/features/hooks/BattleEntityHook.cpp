#include "pch.h"
#include "BattleEntityHook.h"

#include "core/events/event_manager.h"
#include "user/cheat/features/combat/OneHitKill.h"

namespace cheat::features
{
    bool BattleEntityHook::s_oneHitKillEnabled = false;
    bool BattleEntityHook::s_godModeEnabled = false;

    BattleEntityHook::BattleEntityHook()
        : FeatureBase("Battle Entity", "Hooks for BattleEntity features",
                      FeatureSection::Hooks)
    {
        HookManager::install(BattleEntity::AddHitPoint(), hBattleEntity_AddHitPoint);
        EventManager::onOneHitKillEnabled.addListener<&BattleEntityHook::onOneHitKillEnabled>();
        EventManager::onOneHitKillDisabled.addListener<&BattleEntityHook::onOneHitKillDisabled>();
        EventManager::onGodModeEnabled.addListener<&BattleEntityHook::onGodModeEnabled>();
        EventManager::onGodModeDisabled.addListener<&BattleEntityHook::onGodModeDisabled>();
    }

    void BattleEntityHook::onOneHitKillEnabled()
    {
        s_oneHitKillEnabled = true;
    }

    void BattleEntityHook::onOneHitKillDisabled()
    {
        s_oneHitKillEnabled = false;
    }

    void BattleEntityHook::onGodModeEnabled()
	{
		s_godModeEnabled = true;
	}

    void BattleEntityHook::onGodModeDisabled()
    {
        s_oneHitKillEnabled = false;
    }

    int64_t BattleEntityHook::hBattleEntity_AddHitPoint(BattleEntity* _this, int64_t value)
    {
        if (s_oneHitKillEnabled)
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
        }

        if (s_godModeEnabled)
        {
            if (_this->TacticEntityType() == TacticEntityType_Enum::Student)
            {
                _this->Damaged(nullptr); // So OnDamaged event won't be invoked
                _this->HitPoint(0);
                _this->HitPointBefore(0);
                return 0;
            }   
        }

        return CALL_ORIGINAL(hBattleEntity_AddHitPoint, _this, value);
    }
}

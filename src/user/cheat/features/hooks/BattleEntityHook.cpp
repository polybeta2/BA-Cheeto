#include "pch.h"
#include "BattleEntityHook.h"

#include "user/cheat/features/combat/OneHitKill.h"
#include "user/cheat/features/player/GodMode.h"

namespace cheat::features
{
    BattleEntityHook::BattleEntityHook()
        : FeatureBase("Battle Entity", "Hooks for BattleEntity features",
                      FeatureSection::Hooks)
    {
        HookManager::install(BattleEntity::AddHitPoint(), BattleEntity_AddHitPoint_Hook);
    }

    int64_t BattleEntityHook::BattleEntity_AddHitPoint_Hook(BattleEntity* _this, int64_t value)
    {
        auto ohk = OneHitKill::getInstance();
        auto gm = GodMode::getInstance();

        if (ohk->isEnabled())
        {
            if (_this->TacticEntityType() != TacticEntityType_Enum::Student)
            {
                _this->HitPoint(1);
                _this->HitPointBefore(1);
            }
        }

        if (gm->isEnabled())
        {
            if (_this->TacticEntityType() == TacticEntityType_Enum::Student)
            {
                // LOG_DEBUG("Add HitPoint {}, HitPointBefore {}, MaxHPCapGauge {},", _this->HitPoint(), _this->HitPointBefore(), _this->MaxHPCapGauge());
                _this->Damaged(nullptr); // So OnDamaged event won't be invoked
                return 0;
            }
        }

        return CALL_ORIGINAL(BattleEntity_AddHitPoint_Hook, _this, value);
    }
}

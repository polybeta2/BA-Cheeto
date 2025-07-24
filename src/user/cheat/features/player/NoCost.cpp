#include "pch.h"
#include "NoCost.h"

namespace cheat::features
{
    NoCost::NoCost()
        : FeatureBase("No Cost", "Removes skill costs and enables instant regeneration",
                      FeatureSection::Player)
    {
        HookManager::install(PlayerSkillCardManager::ProcessSkillCard(), hPlayerSkillCardManager_ProcessSkillCard);
    }

    void NoCost::hPlayerSkillCardManager_ProcessSkillCard(PlayerSkillCardManager* _this)
    {
        if (s_instance->isEnabled())
        {
            _this->CurCost(_this->MaxCost());
            _this->RegenStartDelayFrame(0);
        }

        CALL_ORIGINAL(hPlayerSkillCardManager_ProcessSkillCard, _this);
    }
}

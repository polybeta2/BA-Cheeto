#include "pch.h"
#include "NoCost.h"

namespace cheat::features
{
    NoCost::NoCost()
        : FeatureBase("No Cost", "Removes skill costs and enables instant regeneration",
                      FeatureSection::Player)
    {
        PlayerSkillCardManager::ProcessSkillCard_Hook().set(PlayerSkillCardManager_ProcessSkillCard_Hook);
    }

    void NoCost::PlayerSkillCardManager_ProcessSkillCard_Hook(PlayerSkillCardManager* _this)
    {
        if (s_instance->isEnabled())
        {
            _this->CurCost(_this->MaxCost());
            _this->RegenStartDelayFrame(0);
        }

        PlayerSkillCardManager::ProcessSkillCard_Hook().call(_this);
    }
}

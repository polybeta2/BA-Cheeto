#include "pch.h"
#include "NoCost.h"

namespace cheat::features
{
    NoCost::NoCost()
        : FeatureBase("No Cost", "Removes skill costs and enables instant regeneration",
                      FeatureSection::Player)
    {
    }

    void NoCost::draw()
    {
    }

    void NoCost::onEnable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s enabled", getName());
    }

    void NoCost::onDisable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s disabled", getName());
    }

    void NoCost::hProcessSkillCard(PlayerSkillCardManager* _this)
    {
        if (s_instance->isEnabled())
        {
            _this->CurCost(_this->MaxCost());
            _this->RegenStartDelayFrame(0);
        }

        CALL_ORIGINAL(hProcessSkillCard, _this);
    }

    bool NoCost::init()
    {
        return HookManager::install(PlayerSkillCardManager::ProcessSkillCard(), hProcessSkillCard);
    }
}

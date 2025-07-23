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
        ImGui::Checkbox("No Skill Cost", &m_enabled);
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
        // TODO: Enable field, GUI, etc.
        _this->CurCost(_this->MaxCost());
        _this->RegenStartDelayFrame(0);

        CALL_ORIGINAL(hProcessSkillCard, _this);
    }

    bool NoCost::init()
    {
        try
        {
            // TODO modularize this. im just busy rn
            HookManager::install(PlayerSkillCardManager::ProcessSkillCard(), hProcessSkillCard);
            LOG_INFO("%s initialized successfully", getName());
            return true;
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("Failed to initialize $s: %s", getName(), e.what());
            return false;
        }
    }
}

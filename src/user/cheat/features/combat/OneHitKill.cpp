#include "pch.h"
#include "OneHitKill.h"

#include "core/events/event_manager.h"

namespace cheat::features
{
    OneHitKill::OneHitKill()
        : FeatureBase("One Hit Kill", "Enemies die in one hit",
                      FeatureSection::Combat)
    {
    }

    void OneHitKill::onEnable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s enabled", getName().c_str());
        EventManager::onOneHitKillEnabled();
    }

    void OneHitKill::onDisable()
    {
        // TODO: replace with imgui toast
        LOG_INFO("%s disabled", getName().c_str());
        EventManager::onOneHitKillDisabled();
    }
}
